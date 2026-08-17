# This script compiles and runs the day-one diagnostic. It never edits source files.
# Prerequisite: MSYS2 UCRT64 GCC. No third-party C library is required.

$ErrorActionPreference = "Stop"

$gccPath = "C:\msys64\ucrt64\bin\gcc.exe"
$gccDirectory = Split-Path -Parent $gccPath
$exerciseRoot = $PSScriptRoot
$diagnosticRoot = Join-Path $exerciseRoot "diagnostic"
$buildDirectory = Join-Path $env:TEMP "embedded_day01_diagnostic_build"
$testProgram = Join-Path $buildDirectory "day01_diagnostic.exe"

if (-not (Test-Path -LiteralPath $gccPath)) {
    Write-Host "GCC was not found at: $gccPath" -ForegroundColor Red
    exit 2
}

New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null
$env:Path = $gccDirectory + ";" + $env:Path

Write-Host "Compiling day-one C diagnostic..." -ForegroundColor Cyan
& $gccPath `
    -std=c11 `
    -Wall `
    -Wextra `
    -Werror `
    -I $diagnosticRoot `
    (Join-Path $diagnosticRoot "day01_baseline.c") `
    (Join-Path $diagnosticRoot "test_day01_baseline.c") `
    -o $testProgram

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed. Fix the first compiler message above." -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host "Build succeeded. Running diagnostic..." -ForegroundColor Green
& $testProgram
exit $LASTEXITCODE
