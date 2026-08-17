# Runs both exercise suites in separate PowerShell processes and prints the next action.
# It does not edit source files and requires no third-party library.

$ErrorActionPreference = "Stop"

$exerciseRoot = $PSScriptRoot
$dayScript = Join-Path $exerciseRoot "run_day01_diagnostic.ps1"
$ringScript = Join-Path $exerciseRoot "run_tests.ps1"

Write-Host "=== 1/2 Day-one C diagnostic ===" -ForegroundColor Cyan
& powershell.exe -NoProfile -ExecutionPolicy Bypass -File $dayScript
$dayExitCode = $LASTEXITCODE

Write-Host "`n=== 2/2 Ring buffer ===" -ForegroundColor Cyan
& powershell.exe -NoProfile -ExecutionPolicy Bypass -File $ringScript
$ringExitCode = $LASTEXITCODE

Write-Host "`n=== Next action ===" -ForegroundColor Cyan
if ($dayExitCode -ne 0) {
    Write-Host "Finish diagnostic/day01_baseline.c before the ring buffer." -ForegroundColor Yellow
    Write-Host "If blocked, read the day-one quick reference and then the staged hints."
    exit 1
}

if ($ringExitCode -ne 0) {
    Write-Host "The diagnostic passed. Implement only rb_init today." -ForegroundColor Yellow
    exit 1
}

Write-Host "Both suites passed. Record evidence and prepare the oral explanation." -ForegroundColor Green
exit 0
