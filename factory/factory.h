#pragma once

#include "parser.h"
#include "shape.h"

Shape* create_shape(const Tokens* tokens);
void free_tokens(Tokens* tokens);