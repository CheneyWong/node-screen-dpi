A NAPI Native C++ Addons to get screen dpi on Windows.

Example
=======

```js

const {GetScreen} = require("node-screen-dpi");

const screen = GetScreen(); // {dpi: i,...}

```

Installation
============

`npm install node-screen-dpi`

You will need C/C++ build tools and Python 2.7 (node-gyp) to build this module.