﻿#include "Engine/Graphics/RHI/RHI.hpp"
#include "Engine/Graphics/RHI/ResourceView.hpp"
#include "RHITexture.hpp"
#include "Engine/Debug/ErrorWarningAssert.hpp"

ShaderResourceView* RHITexture::srv(uint mipLevel) const {

  ResourceViewInfo info(mipLevel, ResourceViewInfo::MAX_POSSIBLE, 0, ResourceViewInfo::MAX_POSSIBLE, DescriptorPool::Type::TextureSrv);

  auto kv = mSrvs.find(info);

  if (kv == mSrvs.end() && is_set(mBindingFlags, BindingFlag::ShaderResource)) {
    ShaderResourceView::sptr_t ptr = ShaderResourceView::create(
        shared_from_this(), info.mostDetailedMip, 
        info.mipCount, info.firstArraySlice, info.arraySize);

    ENSURES(ptr->info() == info);

    mSrvs[info] = ptr;
    return ptr.get();
  }

  return mSrvs[info].get();

}

void RHITexture::invalidateViews() {
  mSrvs.clear();
}


const RenderTargetView* RHITexture::rtv(uint mipLevel) const {

  ResourceViewInfo info(mipLevel, 1, 0, ResourceViewInfo::MAX_POSSIBLE, DescriptorPool::Type::TextureSrv);

  auto kv = mRtvs.find(info);

  if (kv == mRtvs.end() && is_set(mBindingFlags, BindingFlag::RenderTarget)) {
    RenderTargetView::sptr_t ptr = RenderTargetView::create(
      shared_from_this(), info.mostDetailedMip,
      info.firstArraySlice, info.arraySize);

    ENSURES(ptr->info() == info);

    mRtvs[info] = ptr;

    return ptr.get();
  }
  return mRtvs[info].get();
}

const DepthStencilView* RHITexture::dsv(uint mipLevel) const {
  ResourceViewInfo info(mipLevel, 1, 0, ResourceViewInfo::MAX_POSSIBLE, DescriptorPool::Type::Dsv);

  auto kv = mDsvs.find(info);

  if (kv == mDsvs.end() && is_set(mBindingFlags, BindingFlag::DepthStencil)) {
    DepthStencilView::sptr_t ptr = DepthStencilView::create(
      shared_from_this(), info.mostDetailedMip,
      info.firstArraySlice, info.arraySize);

    ENSURES(ptr->info() == info);

    mDsvs[info] = ptr;

    return ptr.get();
  }
  return mDsvs[info].get();
}

const UnorderedAccessView* RHITexture::uav(uint mipLevel) const {
  ResourceViewInfo info(mipLevel, 1, 0, mArraySize, DescriptorPool::Type::TextureUav);

  auto kv = mUavs.find(info);

  if(kv == mUavs.end() && is_set(mBindingFlags, BindingFlag::UnorderedAccess)) {
    UnorderedAccessView::sptr_t ptr = UnorderedAccessView::create(
      shared_from_this(), info.mostDetailedMip,
      info.firstArraySlice, info.arraySize
    );

    ENSURES(ptr->info() == info);

    mUavs[info] = ptr;

    return ptr.get();
  }

  return mUavs[info].get();
}
