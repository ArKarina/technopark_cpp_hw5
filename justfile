run: build
  ./build/app

format:
  clang-format -std=c++11 --dry-run --Werror src/*.cpp include/*.h

tidy: cmake
  clang-tidy -std=c++11 -p build src/*.cpp include/*.h

build: cmake
  ninja -Cbuild

cmake:
  cmake -Bbuild -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

app:
  cd build && ./app

tests:
  cd build && cd test && ./SetTests
clean:
  rm -r build
  