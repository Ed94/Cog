clear-host

$path_root    = git rev-parse --show-toplevel
$path_plugins = join-path $path_root 'Plugins'

$path_release  = Join-Path $path_root 'Release'

if ( -not(Test-Path $path_release) ) { New-Item -ItemType Directory -Path $path_release }

$path_cog_zip = join-path $path_release 'Cog.zip'
if (Test-Path $path_cog_zip) { Remove-Item -Path $path_cog_zip }

Get-ChildItem -Path $path_plugins | Compress-Archive -DestinationPath $path_cog_zip
Write-Host "Created zip file at $path_cog_zip"
