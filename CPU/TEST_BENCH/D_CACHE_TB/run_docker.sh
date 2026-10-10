#!/bin/bash
# Build and run D_CACHE_TB with Verilator inside Docker (for hosts where
# Verilator does not run natively, e.g. macOS).
#
# The project root is mounted at the SAME absolute path inside the container,
# because D_CACHE.v and D_CACHE_TB.sv `include sabit_veriler.vh by absolute path.
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"
IMAGE="${VERILATOR_IMAGE:-verilator/verilator:latest}"

docker run --rm \
    -v "$ROOT:$ROOT" \
    -w "$HERE" \
    --entrypoint bash \
    "$IMAGE" -c "
        set -e
        verilator --binary --timing --trace -Wno-fatal -Wno-lint -Wno-style \
            --top-module D_CACHE_tb \
            -Mdir obj_dir \
            '$ROOT/CPU/CACHE/D_CACHE.v' \
            '$HERE/D_CACHE_TB.sv'
        ./obj_dir/VD_CACHE_tb
    "
