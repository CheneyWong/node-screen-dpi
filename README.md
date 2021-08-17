A NAPI Native C++ Addons to get screen dpi on Windows.

Example
=======

```js

const {GetDPI} = require("node-screen-dpi-win");

const dpi = GetDPI(); // {dpi: i}

```

Installation
============

`npm install node-screen-dpi-win`

You will need C/C++ build tools and Python 2.7 (node-gyp) to build this module.