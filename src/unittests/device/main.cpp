#include <base/device/pipelines/coloredquadpipeline.h>
#include <base/memoryallocator/taggednew.h>
#include <base/memoryallocator/bootstrap.h>
#include <base/glewhelper/glewhelper.h>
#include <base/game/game.h>
#include <unittests/device/testtexture.h>


// Tests.
#include "testmemory.h"
#include "testrenderoutputs.h"
#include "testmultisampling.h"
#include "testasyncquery.h"
#include "testgeometryshader.h"

// STL.
#include <iostream>

using namespace ngs;

void test_texture_gles3_plus() {
  // Test pipeline with unnormalized texture values.
  // Note float,int, and unsigned int textures are always accessed unnormalized.
  TestTexture test_texture1(FloatElement, false);
  TestTexture test_texture2(HalfElement, false);
  TestTexture test_texture3(IntElement, false);
  TestTexture test_texture4(UIntElement, false);
  TestTexture test_texture5(ShortElement, false);
  TestTexture test_texture6(UShortElement, false);
  TestTexture test_texture7(CharElement, false);
  TestTexture test_texture8(UCharElement, false);

  // Test pipeline with normalized texture values.
  // Note float,int, and unsigned int textures are always accessed unnormalized.
  TestTexture _test_texture1(FloatElement, true);
  TestTexture _test_texture2(HalfElement, true);
  TestTexture _test_texture3(IntElement, true);
  TestTexture _test_texture4(UIntElement, true);
  //TestTexture<short> _test_texture5(true); // FBOs are not required to support snorm textures.
  //TestTexture2 _test_texture6(UShortElement, true);
  //TestTexture<char> _test_texture7(true); // FBOs are not required to support snorm textures.
  //TestTexture2 _test_pipeline8(UCharElement, true);
}

void test_render_outputs_gles3_plus() {
  // Test pipeline with unnormalized texture values.
  // Note float,int, and unsigned int textures are always accessed unnormalized.
  TestRenderOutputs test_pipeline1(FloatElement, false);
  TestRenderOutputs test_pipeline2(HalfElement, false);
  TestRenderOutputs test_pipeline3(IntElement, false);
  TestRenderOutputs test_pipeline4(UIntElement, false);
  TestRenderOutputs test_pipeline5(ShortElement, false);
  TestRenderOutputs test_pipeline6(UShortElement, false);
  TestRenderOutputs test_pipeline7(CharElement, false);
  TestRenderOutputs test_pipeline8(UCharElement, false);

  // Test pipeline with normalized texture values.
  // Note float,int, and unsigned int textures are always accessed unnormalized.
  TestRenderOutputs _test_pipeline1(FloatElement, true);
  TestRenderOutputs _test_pipeline2(HalfElement, true);
  TestRenderOutputs _test_pipeline3(IntElement, true);
  TestRenderOutputs _test_pipeline4(UIntElement, true);
  //TestRenderOutputs<short> _test_pipeline5(true); // FBOs are not required to support snorm textures.
  //TestRenderOutputs _test_pipeline6(UShortElement, true);
  //TestRenderOutputs<char> _test_pipeline7(true); // FBOs are not required to support snorm textures.
  //TestRenderOutputs _test_pipeline8(UCharElement, true);
}
void test_render_outputs_gles2() {
//  TestRenderOutputs test_pipeline1(CharElement, false);
//  TestRenderOutputs test_pipeline2(CharElement, true);
}

// The opengl window and context should be current at this point.
void test() {
	// Bootstrap all the global objects.
  bootstrap_memory_tracker();
  {
//    std::cerr << "testing textures load/unload ...\n";
//    test_texture_gles3_plus();
//
//    std::cerr << "testinging gpu memory ...\n";
//    TestMemory test_memory;
//
//    std::cerr << "testing gpu render outputs ...\n";
//    test_render_outputs_gles3_plus();

    std::cerr << "testing gpu multi-sampling ...\n";
    TestMultiSampling test_multi_sampling;

    std::cerr << "testing gpu asynchronous queries ...\n";
    TestAsyncQuery test_async_query;

    std::cerr << "testing gpu geometry shaders ...\n";
    TestGeometryShader test_geometry_shader;

    // Done.
    std::cerr << "device testing has pass. 100%\n";
  }
  // Cleanup all the global objects.
  shutdown_memory_tracker();
}


int main(int argc, char **argv) {
  UnitTestGame* game = UnitTestGame::get_instance();
  game->test = test;
  game->run();
  return 0;
}

