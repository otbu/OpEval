# ==============================================================================
cmake_minimum_required (VERSION 3.6)
project (ExpressionEvaluator)
set (CMAKE_C_STANDARD 11)

# ------------------------------------------------------------------------------

# ==============================================================================
# Initialize local variables (non-cache):
set(var_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Sources")
file(GLOB_RECURSE 
	var_SOURCE_FILES
	"${var_SOURCE_DIR}/*.c")
file(GLOB_RECURSE 
	var_HEADER_FILES
	"${var_SOURCE_DIR}/*.h")
# ------------------------------------------------------------------------------

# ==============================================================================
add_executable(tgt_exeBinary 
	"${var_SOURCE_FILES}"
    "${var_HEADER_FILES}")

# ------------------------------------------------------------------------------