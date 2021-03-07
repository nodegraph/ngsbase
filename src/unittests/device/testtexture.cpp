#include <base/memoryallocator/taggednew.h>
#include <base/device/deviceheadersgl.h>
#include <base/device/devicedebug.h>
#include <base/device/pipelines/texturedquadpipeline.h>

// Packed buffers.
#include <base/device/packedbuffers/packedtexture.h>

// Unpacked buffers.
#include <base/device/unpackedbuffers/texture.h>
#include <unittests/device/testtexture.h>

// STL.
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>


using namespace ngs;

#define kWidth 2201
#define kHeight 1201
#define kNumChannels 4

TestTexture::TestTexture(ElementID element_id, bool normalized_access, std::function<void()> swap)
    : _element_id(element_id),
      _normalized_access(normalized_access),
      _swap(swap),
      _packed_texture(NULL),
      _texture(NULL),
      _read_back_packed_texture(NULL),
      _pipeline(new_ff TexturedQuadPipeline()){
  create_packed_texture();
  create_texture();
  read_back_texture();
  check_read_back_texture();
}

TestTexture::~TestTexture() {
  delete_ff(_packed_texture);
  delete_ff(_texture);
  delete_ff(_read_back_packed_texture);
  delete_ff(_pipeline);
}

namespace {
template<class T>
void fill_row_with_random(char* raw);

template<>
void fill_row_with_random<float>(char* raw) {
	float* element = reinterpret_cast<float*>(raw);
	for (size_t j = 0; j < kWidth * kNumChannels; j++) {
		*element = (float)rand()/(float)RAND_MAX - 0.5f;
		++element;
	}
}
template<>
void fill_row_with_random<half>(char* raw) {
	half* element = reinterpret_cast<half*>(raw);
	for (size_t j = 0; j < kWidth * kNumChannels; j++) {
		*element = (float)rand()/(float)RAND_MAX - 0.5f;
		++element;
	}
}
template<>
void fill_row_with_random<int>(char* raw) {
	int* element = reinterpret_cast<int*>(raw);
	for (size_t j = 0; j < kWidth * kNumChannels; j++) {
		*element =rand() - (RAND_MAX/2);
		++element;
	}
}
template<>
void fill_row_with_random<unsigned int>(char* raw) {
	unsigned int* element = reinterpret_cast<unsigned int*>(raw);
	for (size_t j = 0; j < kWidth * kNumChannels; j++) {
		*element = rand();
		++element;
	}
}
template<>
void fill_row_with_random<short>(char* raw) {
	short* element = reinterpret_cast<short*>(raw);
	for (size_t j = 0; j < kWidth * kNumChannels; j++) {
		*element = rand() - (RAND_MAX/2);
		++element;
	}
}
template<>
void fill_row_with_random<unsigned short>(char* raw) {
	unsigned short* element = reinterpret_cast<unsigned short*>(raw);
	for (size_t j = 0; j < kWidth * kNumChannels; j++) {
		*element = rand();
		++element;
	}
}
template<>
void fill_row_with_random<char>(char* raw) {
	char* element = reinterpret_cast<char*>(raw);
	for (size_t j = 0; j < kWidth * kNumChannels; j++) {
		*element = rand()-(RAND_MAX/2);
		++element;
	}
}
template<>
void fill_row_with_random<unsigned char>(char* raw) {
	unsigned char* element = reinterpret_cast<unsigned char*>(raw);
	for (size_t j = 0; j < kWidth * kNumChannels; j++) {
		*element = rand();
		++element;
	}
}
}

void TestTexture::create_packed_texture() {
	// Create a packed texture with a horizontal bar in it.
	_packed_texture = new_ff PackedTexture(_element_id);
	_packed_texture->reallocate(kWidth, kHeight, 1, kNumChannels);

	// Memset the elements to zero.
	char* raw = _packed_texture->get_pixel();
	memset(raw, 0, _packed_texture->get_chunk_geometry().get_num_bytes());

	// Fill in the texture.
	size_t element_size =
			_packed_texture->get_chunk_geometry().get_element_size_bytes();
	size_t row_size = element_size * kNumChannels * kWidth;
	for (int i = 0; i < kHeight; i++) {
		char* raw = _packed_texture->get_pixel(0, i, 0);
		switch (_element_id) {
		case FloatElement:
			fill_row_with_random<float>(raw);
			break;
		case HalfElement:
			fill_row_with_random<half>(raw);
			break;
		case IntElement:
			fill_row_with_random<int>(raw);
			break;
		case UIntElement:
			fill_row_with_random<unsigned int>(raw);
			break;
		case ShortElement:
			fill_row_with_random<short>(raw);
			break;
		case UShortElement:
			fill_row_with_random<unsigned short>(raw);
			break;
		case CharElement:
			fill_row_with_random<char>(raw);
			break;
		case UCharElement:
			fill_row_with_random<unsigned char>(raw);
			break;
		}
	}
}

void TestTexture::create_texture() {
	// Create our texture.
	_texture = new_ff Texture(0, *_packed_texture, _normalized_access);

	// Show the texture in the opengl window.
	_pipeline->set_texture(_texture);
	_pipeline->draw();
	_texture->unbind(0);

	// Swap.
	_swap();
}

void TestTexture::read_back_texture()
{
	// Download the texture to a packed texture.
	_texture->bind(0);
	_read_back_packed_texture = _texture->create_packed_texture();
}

void TestTexture::check_read_back_texture()
{
  // We check the read back packed texture using
  // the packed texture's equality operator.

	// Uncomment to force the two packed textures to be unequal.
	//*_packed_texture->get_pixel(50,50,0)= 'v';
	if (!(*_packed_texture == *_read_back_packed_texture)) {
		std::cerr << "packed textures are not equal\n";
		assert(false);
	}
}

