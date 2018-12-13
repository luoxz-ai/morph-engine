#include "Engine/Graphics/RHI/RHI.hpp"
#include "Engine/Graphics/RHI/ResourceView.hpp"
#include "Texture.hpp"
#include "Engine/Debug/ErrorWarningAssert.hpp"
#include "Engine/Core/Image.hpp"
#include "Engine/File/FileSystem.hpp"


template<typename TexType, typename ...Args>
typename TexType::sptr_t createOrFail(const void* data, size_t size, Args ... args) {
  typename TexType::sptr_t tex = TexType::sptr_t(new TexType(args..., data, size));
  return tex->rhiInit(data, size) ? tex : nullptr;
}


Texture2::sptr_t Texture2::create(uint width, uint height, eTextureFormat format, BindingFlag flag, const void* data, size_t size) {
  return createOrFail<Texture2>(data, size, width, height, format, flag);
}

Texture2::sptr_t Texture2::create(rhi_resource_handle_t res) {
  return Texture2::sptr_t(new Texture2(res));
}

const RenderTargetView& Texture2::rtv() {
  if (!mRtv) {
    mRtv = RenderTargetView::create(shared_from_this());
  }
  return *mRtv;
}

const DepthStencilView* Texture2::dsv() {
  if (mFormat != TEXTURE_FORMAT_D24S8) {
    INFO("try to access a texture which is not supposed to have dsv");
    return nullptr;
  }

  if(!mDsv) {
    mDsv = DepthStencilView::create(shared_from_this());
  }

  return mDsv.get();
}

const UnorderedAccessView* Texture2::uav() const {
  if(!mUav) {
    mUav = UnorderedAccessView::create(shared_from_this());
  }

  return mUav.get();
}

template<>
ResDef<Texture2> Resource<Texture2>::load(const std::string& file) {
  auto name = make_wstring(file);
  if (file == "$default") {
    Texture2* tex = new Texture2(1, 1, TEXTURE_FORMAT_RGBA8, RHIResource::BindingFlag::ShaderResource);
    tex->rhiInit(&Rgba::white, sizeof(vec4));
    setName(*tex, name.c_str());
    return { file, tex };
  }

  FileSystem& vfs = FileSystem::Get();
  auto realPath = vfs.locate(file);

  if (!realPath) return { file, nullptr };

  Image img(realPath->string());

  Texture2* tex = new Texture2(img.dimension().x, img.dimension().y, 
                               img.format(), RHIResource::BindingFlag::ShaderResource);
  tex->rhiInit(img.data(), img.size());
  setName(*tex, name.c_str());
  return { file, tex };
};