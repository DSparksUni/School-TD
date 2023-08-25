#ifndef UNI_UTIL_H_INCLUDED_
#define UNI_UTIL_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>

#define UNI_ALLOC(T) (T*)malloc(sizeof(T))

typedef enum uni_error_t {
    UNI_SUCCESS,
    UNI_ALLOC_ERROR,
    UNI_SDL_WINDOW_INIT_ERROR,
    UNI_SDL_RENDERER_INIT_ERROR,
    UNI_ERROR_COUNT
} uni_error;

#endif  //UNI_UTIL_H_INCLUDED_