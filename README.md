# Mini Render

Minimal format utilities. Bundled with a cli tool named `poster`.


## Usage

Qucik start: 

The cli tool is a HTTP POST peformer that post rendered data to specified endpoint. Example: 

```shell
./poster -t template.json --endpoint https://postman-echo.com/post SITE_ID=LAS_VEGAS DATE=20200911
```

### CLI: `poster [options] formats`

#### Positional arguments:
- `formats`      	format options. example: a=1 b=2

#### Optional arguments:
- `-h` `--help`    	shows help message and exits
- `-v` `--version` 	prints version information and exits
- `-c`           	template base path. default=templates/
- `--retry`      	retry time, default=3
- `--endpoint`   	the endpoint, example: https://example.com/post[Required]
- `-t`           	the template to use. example: example.json[Required]

## Building

### Dependencies

- [libfmt](https://github.com/fmtlib/fmt.git) as format backends for rendering templates
- [argparse](https://github.com/p-ranav/argparse.git) as argument parser
- [curlpp](https://github.com/jpbarrette/curlpp.git) a wrapper of libcurl
- [libcurl](https://curl.haxx.se/libcurl/) as http backends (Can simply installed with the system package manager)

## Templates & API

This repo provides the template rendering interface called `mrender`, if you have a `CMake` managed project, add this repo as subdirectory and link `mrender::code`

```CMake
add_subdirectory(${CMAKE_SOURCE_DIR}/3rd_party/mini-render)
target_link_libraries(mrender
  PUBLIC curl curlpp fmt::fmt mrender::core)
```

For more details, please check [Template Details](TEMPLATE.md)
