# cliTextFormat

A little crossplatform library to format the text on stdout, based on the [SGR parameters](https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_parameters) of the ANSI escape codes (on Windows I had to use the proprietary Console API).

## Build

I used `Visual Studio 2019` (msvc) on Windows and the build-essential package (`make` and `g++`) on linux.

## Compatibility

||Manjaro|Ubuntu|Windows 10|
|---|:---:|:---:|:---:|
|fore/background colors|✓|✓|✓|
|`SGR_BOLD`|✓|✓|✕|
|`SGR_UNDERLINE`|✓|✓|✓|
|`SGR_REVERSE_VIDEO`|✓|✓|✓|
|`SGR_STRIKE_OUT`|✓|✓|✕|
|`SGR_BLINK_SLOW`|✓|✓|✕|

> On up to date systems in Oct. 2020
