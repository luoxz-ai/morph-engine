﻿#include "RHIContext.hpp"

void RHIContext::updateBuffer(const RHIBuffer* buffer, const void* data, size_t offset, size_t byteCount) {
  if (byteCount == 0) {
    byteCount = buffer->size() - offset;
  }

  // falcor try to  tweek size and offset so that it's safe to do the operation
  // I will just assume the input is always legal first

  mCommandsPending = true;

  // Allocate a buffer on the upload heap

  byte* start = (byte*)data + offset;

  RHIBuffer::sptr_t uploadBuffer = RHIBuffer::create(byteCount, RHIBuffer::BindingFlag::None, RHIBuffer::CPUAccess::Write, start);

  copyBufferRegion(buffer, offset, uploadBuffer.get(), 0, byteCount);
}
//
// void RHIContext::updateTexture(RHITexture& texture, void* data) {
//   mCommandsPending = true;
//   // temp version, assume 2d, 1 mip
//   uint subresCount = 1;
//   
//   // if(3d) {}
//   // else {
//   updateTextureSubresources(texture, 0, subresCount, data);
// }

