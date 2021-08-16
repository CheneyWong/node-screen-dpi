"use strict";

const { GetDPI } = require("../lib/index.cjs");

const dpi = GetDPI();
console.log(`Current screen resolution is ${JSON.stringify(dpi)}`);