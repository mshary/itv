%module pyitv

%{
#include <stdlib.h>
#include <string.h>
#include "itv_utils.h"
#include "itv_characters.h"
#include "itv_wrapper.h"
%}

%include "itv_wrapper.h"
