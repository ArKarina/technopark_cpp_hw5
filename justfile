run: build
  ./build/app

format:
  clang-format --dry-run --Werror src/*.cpp include/*.h

tidy: cmake
  clang-tidy -p build src/*.cpp include/*.h

build: cmake
  ninja -Cbuild

cmake:
  cmake -Bbuild -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

app:
  cd build && ./app

tests:
  cd build && cd test && ./MatrixCalculatorTests
clean:
  rm -r build
  