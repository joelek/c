#!/bin/sh

echo "Arcane build system"
echo ""

COMPILER_OPTIONS="-std=c11 -pedantic -Wall -Wextra -O3 -s -D DEBUG"

SOURCES=(
  "allocator"
  "bit_reader"
  "buffer"
  "buffer_reader"
  "header"
  "lib"
  "ram_buffer"
  "reader"
  "reader_bit_reader"
)

TARGETS=(
  "main"
)

TESTS=(
  "buffer_reader_test"
  "ram_buffer_test"
  "reader_bit_reader_test"
)

VECTOR_TYPES=(
  "byte"
)

GENERATED_HEADERS=()

for i in ${VECTOR_TYPES[@]}; do
  cat vector.c | sed -e "s/GENERIC_TYPE/$i/g" > vector_$i.c
  cat vector.h | sed -e "s/GENERIC_TYPE/$i/g" > vector_$i.h
  GENERATED_HEADERS+="#include \"vector_$i.h\"\n"
  SOURCES+=" vector_$i"
done

echo -e $GENERATED_HEADERS > generated_headers.h

mkdir -p build

OBJECTS=()

for i in ${SOURCES[@]}; do
  OBJECTS+=" build/$i.o"
done

for i in ${SOURCES[@]}; do
  gcc $COMPILER_OPTIONS -c $i.c -o build/$i.o
done

for i in ${TESTS[@]}; do
  gcc $COMPILER_OPTIONS ${OBJECTS[@]} $i.c -o build/$i
done

TESTS_SUCCESS=0
TESTS_FAILURE=0

for i in ${TESTS[@]}; do
  echo "[$i.c]"
  build/$i
  RETURN_CODE=$?
  if [ $RETURN_CODE -eq 0 ]; then
    TESTS_SUCCESS=`expr $TESTS_SUCCESS + 1`
  else
    TESTS_FAILURE=`expr $TESTS_FAILURE + 1`
  fi
  echo ""
done

echo "success: $TESTS_SUCCESS"
echo "failure: $TESTS_FAILURE"
echo ""

if [ $TESTS_FAILURE -eq 0 ]; then
  for i in ${TARGETS[@]}; do
    gcc $COMPILER_OPTIONS ${OBJECTS[@]} $i.c -o build/$i
  done
fi

for i in ${SOURCES[@]}; do
  rm -f build/$i.o
done

exit $TESTS_FAILURE
