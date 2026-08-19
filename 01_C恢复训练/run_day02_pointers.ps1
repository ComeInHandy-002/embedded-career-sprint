# Compiles and runs the day-two pointer exercises. It never edits source files.

$ErrorActionPreference = "Stop"

$gccPath = "C:\msys64\ucrt64\bin\gcc.exe"
$gccDirectory = Split-Path -Parent $gccPath
$exerciseRoot = $PSScriptRoot
$diagnosticRoot = Join-Path $exerciseRoot "diagnostic"
$buildDirectory = Join-Path $env:TEMP "embedded_day02_pointers_build"
$testProgram = Join-Path $buildDirectory "day02_pointers.exe"

if (-not (Test-Path -LiteralPath $gccPath)) {
    Write-Host "GCC was not found at: $gccPath" -ForegroundColor Red
    exit 2
}

New-Item -ItemType Directory -Path $buildDirectory -Force | Out-Null
$env:Path = $gccDirectory + ";" + $env:Path

Write-Host "Compiling day-two pointer exercises..." -ForegroundColor Cyan
& $gccPath `
    -std=c11 `
    -Wall `
    -Wextra `
    -Werror `
    -I $diagnosticRoot `
    (Join-Path $diagnosticRoot "day02_pointers.c") `
    (Join-Path $diagnosticRoot "test_day02_pointers.c") `
    -o $testProgram

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed. Fix the first compiler message above." -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host "Build succeeded. Running exercises..." -ForegroundColor Green
& $testProgram
exit $LASTEXITCODE
