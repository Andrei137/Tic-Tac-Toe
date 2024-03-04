# If the folder bin doesn't exist, create it
if [ ! -d "bin" ]; then
    mkdir bin
fi

project_dir="$(dirname "${BASH_SOURCE[0]}")"
cmakelists_file="${project_dir}/src/CMakeLists.txt"

# Function to check if CMakeLists.txt has been modified
# Or if the build folder doesn't exist
needs_cmake() {
    if [ ! -d "build" ] || [ "${cmakelists_file}" -nt "${project_dir}" ] || [ "bin/TicTacToe.exe" -nt "bin/TicTacToe" ];  then
        return 0
    else 
        return 1
    fi
}

# Check if run is passed as an argument
if [ "$1" ==  "run" ]; then
    run_executable=true
else
    run_executable=false
fi

# If CMakeLists.txt has been modified or if the build folder doesn't exist
# Run cmake to generate the build folder
if needs_cmake; then
    rm -rf build
    cmake -B build -S src -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=../bin
fi

cd build
make

# If run is passed as an argument, run the executable too
if [ "$run_executable" = true ]; then
    cd ../bin
    ./TicTacToe
fi