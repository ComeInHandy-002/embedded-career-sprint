# This script compiles and runs the tests. It never edits source files.
# Prerequisite: MSYS2 UCRT64 GCC. No third-party C library is required.

$ErrorActionPreference = "Stop"

$gccPath = "C:\msys64\ucrt64\bin\gcc.exe"
$gccDirectory = Split-Path -Parent $gccPath
$exerciseRoot = $PSScriptRoot
$buildDirectory = Join-Path $env:TEMP "embedded_c_recovery_build"
$testProgram = Join-Path $buildDirectory "ring_buffer_tests.exe"

if (-not (Test-Path -LiteralPath $gccPath)) {
    Write-Host "GCC was not found at: $gccPath" -ForegroundColor Red
    Write-Host "Install MSYS2 UCRT64 GCC before running this script."
    exit 2
}

New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null

# GCC starts helper programs and loads DLL files from the same toolchain folder.
# Add that folder only for this script process; this does not change Windows settings.
$env:Path = $gccDirectory + ";" + $env:Path

Write-Host "Compiling ring buffer tests..." -ForegroundColor Cyan
& $gccPath `
    -std=c11 `
    -Wall `
    -Wextra `
    -Werror `
    -I (Join-Path $exerciseRoot "include") `
    (Join-Path $exerciseRoot "src\ring_buffer.c") `
    (Join-Path $exerciseRoot "tests\test_ring_buffer.c") `
    -o $testProgram

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed. Fix the first compiler message above." -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host "Build succeeded. Running tests..." -ForegroundColor Green
& $testProgram
exit $LASTEXITCODE
