#!/bin/bash

BUILD_DIR="build"
VENV_DIR="venv"

clean_build() {
    echo "Cleaning up build directory..."
    [ -f Logs/logs.log ] && rm Logs/logs.log
    rm -rf "$BUILD_DIR"
}

configure() {
    if [ ! -d "$BUILD_DIR" ]; then
        echo "Configuring project..."
        cmake -B "$BUILD_DIR" ${1:+-DCMAKE_BUILD_TYPE="$1"}
    fi
}

build() {
    configure "$1"
    echo "Building project..."
    cmake --build "$BUILD_DIR" --target template
}

build_tests() {
    configure "$1"
    echo "Building tests..."
    cmake --build "$BUILD_DIR" --target template_tests
}

run_analyze() {
    echo "Setting up Python environment for analysis..."
    if [ ! -d "$VENV_DIR" ]; then
        echo "Creating virtual environment..."
        python3 -m venv "$VENV_DIR"
    fi
    source "$VENV_DIR"/bin/activate
    pip install --upgrade pip --quiet
    pip install matplotlib --quiet
    if [ -f "Logs/analyze.py" ]; then
        echo "Running analysis script..."
        python3 Logs/analyze.py
    else
        echo "Error: Logs/analyze.py not found!"
    fi
    deactivate
}

case "$1" in
    --clean|-c)
        clean_build
        build
        build_result=$?
        ;;
    --debug|-d)
        build "Debug"
        build_result=$?
        if [ $build_result -eq 0 ]; then
            lldb ./"$BUILD_DIR"/template
        fi
        ;;
    --release|-r)
        build "Release"
        build_result=$?
        ;;
    --analyze|-a)
        run_analyze
        exit 0
        ;;
    --tests|-t)
        build_tests
        build_result=$?
        ;;
    --help|-h)
        echo "Usage: $0 [OPTION]"
        echo "Build and run the project."
        echo
        echo "  --clean, -c    Clean and rebuild"
        echo "  --debug, -d    Build with Debug config and launch lldb"
        echo "  --release, -r  Build with Release config"
        echo "  --tests, -t    Build and run tests"
        echo "  --analyze, -a  Run analysis"
        echo "  --help, -h     Show this help"
        echo
        echo "  (no args)      Build and run"
        exit 0
        ;;
    "")
        build
        build_result=$?
        ;;
    *)
        echo "Unknown option: $1"
        echo "Usage: $0 [--clean|--debug|--release|--tests|--analyze|--help]"
        exit 1
        ;;
esac

if [ $build_result -eq 0 ] && [ "$1" != "--debug" ] && [ "$1" != "-d" ] && [ "$1" != "--release" ] && [ "$1" != "-r" ]; then
    if [ "$1" == "--tests" ] || [ "$1" == "-t" ]; then
        echo "Running tests..."
        cd "$BUILD_DIR" && ctest -V && cd - > /dev/null
    else
        echo "Running project..."
        ./"$BUILD_DIR"/template
    fi
elif [ $build_result -ne 0 ]; then
    echo "Build failed."
fi
