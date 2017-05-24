#include <base/device/unpackedbuffers/vertexbuffer.h>
#include <base/device/deviceheadersgl.h>
#include <base/device/devicedebug.h>

namespace ngs {

VertexBuffer::VertexBuffer()
    : Buffer(GL_ARRAY_BUFFER) {
}

VertexBuffer::~VertexBuffer() {
}

}
