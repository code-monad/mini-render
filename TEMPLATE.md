# Mini Render Template

## A Quick Look

```json
{
"comment": "A example post request of json render",
"site_id": "%SITE_ID%",
"dt": %DATE%
}
```

Every part surrounded with pair of `%` will be formatted if format argument presents.

For example, the `%SITE_ID%` will be formatted with `"SITE_ID=LAS_VEGAS"`, `%DATE%` will be formatted with "DATE=20200911", the render results will be: 

```json
{
"comment": "A example post request of json render",
"site_id": "LAS_VEGAS",
"dt": 20200911
}
```

## API Usage

Check [template header](include/mrender/template.hh#L17) and [render header](include/mrender/render.hh)

Currently we have a `plain text` and `json` template/render bultin.(Check [Render](include/mrender/render.hh#L61) and [JsonRender](include/mrender/render.hh#L62))

If you want to add your own format of template, you could do like above:

```c++
// NOTICE: MUST IMPLEMENT THESE IN HEADER FILE

namespace mrender{
using DuckTemplate = Template<DuckType>;
template<> inline const std::string DuckTemplate::content() { return _content.guak();} // dummy code, how we stringify a duck?
template<> inline DockTemplate& DuckTemplate::format(const std::unordered_map<std::string, std::string>& format_args){ // dummy code, How we format a duck??
  // the formatting logic
  for(auto& [arg, val]: format_args) {
  // dummy codes...
    duck.eat(val);
    duck.guak(arg);
    // and more...
  }
  // ...
  return *this;
}
}
```

If you want your own render, also do similarly:

```c++
// NOTICE: MUST PUT THESE IN HEADER FILE
namespace mrender {
using DuckRender = render<DuckType>;
template<> inline DuckTemplate& Render::get_template() {
        _template = DuckTemplate(_raw_template);
        _template.guak(); // just dummy codes...
        return _template;
}
}
```

In your C++ code, call:

```c++
// assume that our template is duck.template, contents inside are:
// %NAME% says, "I'm a DUCK an wearing %CLOTH%!"

auto duck_render= std::make_shared<mrender::DuckRender>("duck.template");

std::cout << duck_render->produce({{"NAME", "Dolnad Duck"}, {"CLOTH", "Seirafuku"}});
```
within the most common logic, we may print:

```console
code@lab-11:~$ ./duck
Dolnad Duck says, I'm a DUCK an wearing Seirafuku! # Just a possible outputs. Depends on the implementation of "Ducktype"

```
