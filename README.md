# C++26 Reflection Demo

Requires [Bloomberg's clang-p2996](https://github.com/bloomberg/clang-p2996).

## Setup

```sh
git clone --depth=1 --branch p2996 https://github.com/bloomberg/clang-p2996.git
cmake -S clang-p2996/llvm -B clang-p2996/build -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" \
  -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
  -DLLVM_TARGETS_TO_BUILD=AArch64 \
  -DCLANG_DEFAULT_CXX_STDLIB=libc++ \
  -DLLVM_PARALLEL_LINK_JOBS=1 \
  -DLLVM_ENABLE_ASSERTIONS=OFF
cmake --build clang-p2996/build -j$(sysctl -n hw.ncpu)  # 2-3 hours
cmake --install clang-p2996/build --prefix ~/.local/clang-p2996
```

## Build & Run

```sh
./build.sh
```

## Quick Reference

### Core operators

| Code | Meaning |
|---|---|
| `^^E` | Reflect entity `E` into `std::meta::info` |
| `[:r:]` | Splice a reflection back into code |
| `p.[:r:]` | Access a reflected member through an object |

### Key functions (all `consteval`, in `<meta>`)

| Function | Returns | Works on |
|---|---|---|
| `enumerators_of(^^E)` | `vector<info>` | enums |
| `nonstatic_data_members_of(^^T, ctx)` | `vector<info>` | structs/classes |
| `members_of(^^T, ctx)` | `vector<info>` | structs/classes (all members) |
| `identifier_of(r)` | `string_view` | any named entity |
| `display_string_of(r)` | `string_view` | human-readable name (types etc.) |
| `type_of(r)` | `info` | the type of an entity |
| `parent_of(r)` | `info` | enclosing scope |
| `dealias(r)` | `info` | resolves `using` aliases |
| `is_enum_type(r)`, `is_class_type(r)`, ... | `bool` | type queries |
| `offset_of(r)`, `size_of(r)` | `size_t` | layout info |

### `template for`

Compile-time expansion — unrolls once per element. Not a runtime loop.

```cpp
template for (constexpr auto e : range) { ... }
```

`constexpr` on the element variable is required.

### `define_static_array`

Metafunctions return `vector<info>`, which heap-allocates (not constexpr-friendly).
`define_static_array` bakes it into a constexpr `span` that `template for` can use.

```cpp
constexpr auto arr = define_static_array(enumerators_of(^^Color));
template for (constexpr auto e : arr) { ... }
```

### `access_context`

Controls visibility for member-queries:

- `unprivileged()` — global scope (private members hidden)
- `unchecked()` — bypass access checks (all members visible)
- `current()` — current function's scope

## Common mistakes

- `enumerators_of` is **only for enums**. Use `nonstatic_data_members_of` for structs.
- `std::vector<info>` cannot be stored in a `constexpr` variable. Always use `define_static_array`.
- Splice `[:e:]` gives a member designator, not a value. Access via `object.[:e:]` or `this->[:e:]`.
- `type_of(r)` returns raw `info` — wrap in `display_string_of` to print as a string.
- All reflection functions are `consteval` (compile-time only). Their results can only "escape" to runtime via `[:splice:]`.

## Reference

The full API is in `<meta>` header at `~/.local/clang-p2996/include/c++/v1/meta` (lines ~42–400).
