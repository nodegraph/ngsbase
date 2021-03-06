#pragma once

#include <base/glewhelper/glewhelper_export.h>

struct GLEWContextStruct;
typedef struct GLEWContextStruct GLEWContext;

// This function is required by the MX version of glew.
// This allows us to initialize glew on multiple threads.
GLEWHELPER_EXPORT GLEWContext* glewGetContext();

GLEWHELPER_EXPORT void start_glew();
GLEWHELPER_EXPORT void finish_glew();

