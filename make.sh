#!/bin/sh

COMPILER_OPTIONS="-std=c11 -pedantic -Wall -Wextra -O3"

SOURCES=(
  "bit_reader"
  "buffer"
  "buffer_reader"
  "header"
  "lib"
  "ram_buffer"
  "reader"
)

TARGETS=(
  "main"
)

TESTS=(
  "buffer_reader_test"
  "ram_buffer_test"
)

mkdir -p build

OBJECTS=()

for i in ${SOURCES[@]}; do
  OBJECTS+=" build/$i.o"
done

for i in ${SOURCES[@]}; do
  gcc $COMPILER_OPTIONS -DDEBUG -c $i.c -o build/$i.o
done

for i in ${TESTS[@]}; do
  gcc $COMPILER_OPTIONS -DDEBUG ${OBJECTS[@]} $i.c -o build/$i
done

for i in ${SOURCES[@]}; do
  rm -f build/$i.o
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
  for i in ${SOURCES[@]}; do
    gcc $COMPILER_OPTIONS -s -c $i.c -o build/$i.o
  done

  for i in ${TARGETS[@]}; do
    gcc $COMPILER_OPTIONS -s ${OBJECTS[@]} $i.c -o build/$i
  done

  for i in ${SOURCES[@]}; do
    rm -f build/$i.o
  done
fi

exit $TESTS_FAILURE
