#pragma once
#include "RHI.hpp"

class RHIResource: public std::enable_shared_from_this<RHIResource> {
  friend class RHIContext;
public:
  using handle_t = rhi_resource_handle_t;
  using sptr_t = S<RHIResource>;
  using scptr_t = S<const RHIResource>;

  /** These flags are hints the driver to what pipeline stages the resource will be bound to. 
   */
  enum class BindingFlag: uint {
    None = 0x0,             ///< The resource will not be bound the pipeline. Use this to create a staging resource
    VertexBuffer = 0x1,     ///< The resource will be bound as a vertex-buffer
    IndexBuffer = 0x2,      ///< The resource will be bound as a index-buffer
    ConstantBuffer = 0x4,   ///< The resource will be bound as a constant-buffer
    StreamOutput = 0x8,     ///< The resource will be bound to the stream-output stage as an output buffer
    ShaderResource = 0x10,  ///< The resource will be bound as a shader-resource
    UnorderedAccess = 0x20, ///< The resource will be bound as an UAV
    RenderTarget = 0x40,    ///< The resource will be bound as a render-target
    DepthStencil = 0x80,    ///< The resource will be bound as a depth-stencil buffer
    IndirectArg = 0x100,    ///< The resource will be bound as an indirect argument buffer
  };

  /** Resource types. Notice there are no array types. Array are controlled using the array size parameter on texture creation.
   */
  enum class Type {
    Buffer,                 ///< Buffer. Can be bound to all shader-stages
    Texture1D,              ///< 1D texture. Can be bound as render-target, shader-resource and UAV
    Texture2D,              ///< 2D texture. Can be bound as render-target, shader-resource and UAV
    Texture3D,              ///< 3D texture. Can be bound as render-target, shader-resource and UAV
    TextureCube,            ///< Texture-cube. Can be bound as render-target, shader-resource and UAV
    Texture2DMultisample,   ///< 2D multi-sampled texture. Can be bound as render-target, shader-resource and UAV
  };

  /** Resource state. Keeps track of how the resource was last used
  */
  enum class State : uint {
    Undefined,
    PreInitialized,
    Common,
    VertexBuffer,
    ConstantBuffer,
    IndexBuffer,
    RenderTarget,
    UnorderedAccess,
    DepthStencil,
    ShaderResource,
    StreamOut,
    IndirectArg,
    CopyDest,
    CopySource,
    ResolveDest,
    ResolveSource,
    Present,
    GenericRead,
    Predication,
    NonPixelShader,
#ifdef MORPH_DXR
    AccelerationStructure,
#endif
  };

  handle_t handle() const { return mRhiHandle; };

  inline State state() const { return mState; }
  inline Type type() const { return mType; }

  virtual ~RHIResource();
protected:
  RHIResource(Type type, BindingFlag bindings): mType(type), mBindingFlags(bindings) {}

  handle_t mRhiHandle;
  Type mType;
  BindingFlag mBindingFlags;
  mutable State mState;
};

enum_class_operators(RHIResource::BindingFlag);

inline RHIResource::~RHIResource() {}

// code structure idea adpot from Falcor Engine: Source/API/Resource.h