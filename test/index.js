"use strict";

const { GetScreen } = require("../lib/index.js");

const screen = GetScreen();
console.log(`Current screen resolution is ${JSON.stringify(screen)}`);