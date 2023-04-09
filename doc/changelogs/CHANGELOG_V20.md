# Node.js 20 ChangeLog

<!--lint disable maximum-line-length no-literal-urls prohibited-strings-->

<table>
<tr>
<th>Current</th>
</tr>
<tr>
<td>
<b><a href="#20.0.0">20.0.0</a></b><br/>
</td>
</tr>
</table>

* Other Versions
  * [19.x](CHANGELOG_V19.md)
  * [18.x](CHANGELOG_V18.md)
  * [17.x](CHANGELOG_V17.md)
  * [16.x](CHANGELOG_V16.md)
  * [15.x](CHANGELOG_V15.md)
  * [14.x](CHANGELOG_V14.md)
  * [13.x](CHANGELOG_V13.md)
  * [12.x](CHANGELOG_V12.md)
  * [11.x](CHANGELOG_V11.md)
  * [10.x](CHANGELOG_V10.md)
  * [9.x](CHANGELOG_V9.md)
  * [8.x](CHANGELOG_V8.md)
  * [7.x](CHANGELOG_V7.md)
  * [6.x](CHANGELOG_V6.md)
  * [5.x](CHANGELOG_V5.md)
  * [4.x](CHANGELOG_V4.md)
  * [0.12.x](CHANGELOG_V012.md)
  * [0.10.x](CHANGELOG_V010.md)
  * [io.js](CHANGELOG_IOJS.md)
  * [Archive](CHANGELOG_ARCHIVE.md)

<a id="20.0.0"></a>

## 2023-04-18, Version 20.0.0 (Current), @RafaelGSS

We're excited to announce the release of Node.js 20! Highlights include the update of the V8 JavaScript engine to 11.3, the Node.js Permission Model,
a stable test\_runner, and improved interoperability of WebCryptoAPI.

As a reminder, Node.js 20 will enter long-term support (LTS) in October, but until then, it will be the "Current" release for the next six months.
We encourage you to explore the new features and benefits offered by this latest release and evaluate their potential impact on your applications.

### Notable Changes

#### Permission Model

Node.js now has an experimental feature called the Permission Model.
It allows developers to restrict access to specific resources during program execution, such as file system operations,
child process spawning, and worker thread creation.
The API exists behind a flag `--experimental-permission` which when enabled will restrict access to all available permissions.
By using this feature, developers can prevent their applications from accessing or modifying sensitive data or running potentially harmful code.
More information about the Permission Model can be found in the [Node.js documentation](https://nodejs.org/api/permissions.html#process-based-permissions).

The Permission Model was a contribution by Rafael Gonzaga in [#44004](https://github.com/nodejs/node/pull/44004).

#### V8 11.3

The V8 engine is updated to version 11.3, which is part of Chromium 113.
This version includes three new features to the JavaScript API:

* [String.prototype.isWellFormed and toWellFormed](https://chromestatus.com/feature/5200195346759680)
* [Methods that change Array and TypedArray by copy](https://chromestatus.com/feature/5068609911521280)
* [Resizable ArrayBuffer and growable SharedArrayBuffer](https://chromestatus.com/feature/4668361878274048)
* [RegExp v flag with set notation + properties of strings](https://chromestatus.com/feature/5144156542861312)
* [WebAssembly Tail Call](https://chromestatus.com/feature/5423405012615168)

The V8 update was a contribution by Michaël Zasso in [#47251](https://github.com/nodejs/node/pull/47251).

#### Deprecations and Removals

* \[[`3bed5f11e0`](https://github.com/nodejs/node/commit/3bed5f11e0)] - **(SEMVER-MAJOR)** **url**: runtime-deprecate url.parse() with invalid ports (Rich Trott) [#45526](https://github.com/nodejs/node/pull/45526)

`url.parse()` accepts URLs with ports that are not numbers. This behavior might result in host name spoofing with unexpected input.
These URLs will throw an error in future versions of Node.js, as the WHATWG URL API does already.
Starting with Node.js 20, these URLS cause `url.parse()` to emit a warning.

#### Other Notable Changes

##### Stable Test Runner

The recent update to Node.js, version 20, includes an important change to the test\_runner module. The module has been marked as stable after a recent update.
Previously, the test\_runner module was experimental, but this change marks it as a stable module that is ready for production use.

Contributed by Colin Ihrig in [#46983](https://github.com/nodejs/node/pull/46983)

##### WebCryptoAPI

WebCryptoAPI functions' arguments are now coersed and validated as per their WebIDL definitions like in other Web Crypto API implementations.
This further improves interoperability with other implementations of Web Crypto API.

This change was made by Filip Skokan in [#46067](https://github.com/nodejs/node/pull/46067).

### Semver-Major Commits

* \[[`9fafb0a090`](https://github.com/nodejs/node/commit/9fafb0a090)] - **(SEMVER-MAJOR)** **async\_hooks**: deprecate the AsyncResource.bind asyncResource property (James M Snell) [#46432](https://github.com/nodejs/node/pull/46432)
* \[[`7bc0e6a4e7`](https://github.com/nodejs/node/commit/7bc0e6a4e7)] - **(SEMVER-MAJOR)** **buffer**: graduate File from experimental and expose as global (Khafra) [#47153](https://github.com/nodejs/node/pull/47153)
* \[[`671ffd7825`](https://github.com/nodejs/node/commit/671ffd7825)] - **(SEMVER-MAJOR)** **buffer**: use min/max of `validateNumber` (Deokjin Kim) [#45796](https://github.com/nodejs/node/pull/45796)
* \[[`ab1614d280`](https://github.com/nodejs/node/commit/ab1614d280)] - **(SEMVER-MAJOR)** **build**: reset embedder string to "-node.0" (Michaël Zasso) [#47251](https://github.com/nodejs/node/pull/47251)
* \[[`c1bcdbcf79`](https://github.com/nodejs/node/commit/c1bcdbcf79)] - **(SEMVER-MAJOR)** **build**: warn for gcc versions earlier than 10.1 (Richard Lau) [#46806](https://github.com/nodejs/node/pull/46806)
* \[[`649f68fc1e`](https://github.com/nodejs/node/commit/649f68fc1e)] - **(SEMVER-MAJOR)** **build**: reset embedder string to "-node.0" (Yagiz Nizipli) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`9374700d7a`](https://github.com/nodejs/node/commit/9374700d7a)] - **(SEMVER-MAJOR)** **crypto**: remove DEFAULT\_ENCODING (Tobias Nießen) [#47182](https://github.com/nodejs/node/pull/47182)
* \[[`1640aeb680`](https://github.com/nodejs/node/commit/1640aeb680)] - **(SEMVER-MAJOR)** **crypto**: remove obsolete SSL\_OP\_\* constants (Tobias Nießen) [#47073](https://github.com/nodejs/node/pull/47073)
* \[[`c2e4b1fa9a`](https://github.com/nodejs/node/commit/c2e4b1fa9a)] - **(SEMVER-MAJOR)** **crypto**: remove ALPN\_ENABLED (Tobias Nießen) [#47028](https://github.com/nodejs/node/pull/47028)
* \[[`3ef38c4bd7`](https://github.com/nodejs/node/commit/3ef38c4bd7)] - **(SEMVER-MAJOR)** **crypto**: use WebIDL converters in WebCryptoAPI (Filip Skokan) [#46067](https://github.com/nodejs/node/pull/46067)
* \[[`08af023b1f`](https://github.com/nodejs/node/commit/08af023b1f)] - **(SEMVER-MAJOR)** **crypto**: runtime deprecate replaced rsa-pss keygen parameters (Filip Skokan) [#45653](https://github.com/nodejs/node/pull/45653)
* \[[`7eb0ac3cb6`](https://github.com/nodejs/node/commit/7eb0ac3cb6)] - **(SEMVER-MAJOR)** **deps**: patch V8 to support compilation on win-arm64 (Michaël Zasso) [#47251](https://github.com/nodejs/node/pull/47251)
* \[[`a7c129f286`](https://github.com/nodejs/node/commit/a7c129f286)] - **(SEMVER-MAJOR)** **deps**: silence irrelevant V8 warning (Michaël Zasso) [#47251](https://github.com/nodejs/node/pull/47251)
* \[[`6f5655a18e`](https://github.com/nodejs/node/commit/6f5655a18e)] - **(SEMVER-MAJOR)** **deps**: always define V8\_EXPORT\_PRIVATE as no-op (Michaël Zasso) [#47251](https://github.com/nodejs/node/pull/47251)
* \[[`f226350fcb`](https://github.com/nodejs/node/commit/f226350fcb)] - **(SEMVER-MAJOR)** **deps**: update V8 to 11.3.244.4 (Michaël Zasso) [#47251](https://github.com/nodejs/node/pull/47251)
* \[[`d6dae7420e`](https://github.com/nodejs/node/commit/d6dae7420e)] - **(SEMVER-MAJOR)** **deps**: V8: cherry-pick f1c888e7093e (Michaël Zasso) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`56c436533e`](https://github.com/nodejs/node/commit/56c436533e)] - **(SEMVER-MAJOR)** **deps**: fix V8 build on Windows with MSVC (Michaël Zasso) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`51ab98c71b`](https://github.com/nodejs/node/commit/51ab98c71b)] - **(SEMVER-MAJOR)** **deps**: silence irrelevant V8 warning (Michaël Zasso) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`9f84d3eea8`](https://github.com/nodejs/node/commit/9f84d3eea8)] - **(SEMVER-MAJOR)** **deps**: V8: fix v8-cppgc.h for MSVC (Jiawen Geng) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`f2318cd4b5`](https://github.com/nodejs/node/commit/f2318cd4b5)] - **(SEMVER-MAJOR)** **deps**: fix V8 build issue with inline methods (Jiawen Geng) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`16e03e7968`](https://github.com/nodejs/node/commit/16e03e7968)] - **(SEMVER-MAJOR)** **deps**: update V8 to 10.9.194.4 (Yagiz Nizipli) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`cc18fd9608`](https://github.com/nodejs/node/commit/cc18fd9608)] - **(SEMVER-MAJOR)** **events**: refactor to use `validateNumber` (Deokjin Kim) [#45770](https://github.com/nodejs/node/pull/45770)
* \[[`ff92b40ffc`](https://github.com/nodejs/node/commit/ff92b40ffc)] - **(SEMVER-MAJOR)** **http**: close the connection after sending a body without declared length (Tim Perry) [#46333](https://github.com/nodejs/node/pull/46333)
* \[[`2a29df6464`](https://github.com/nodejs/node/commit/2a29df6464)] - **(SEMVER-MAJOR)** **http**: keep HTTP/1.1 conns alive even if the Connection header is removed (Tim Perry) [#46331](https://github.com/nodejs/node/pull/46331)
* \[[`391dc74a10`](https://github.com/nodejs/node/commit/391dc74a10)] - **(SEMVER-MAJOR)** **http**: throw error if options of http.Server is array (Deokjin Kim) [#46283](https://github.com/nodejs/node/pull/46283)
* \[[`ed3604cd64`](https://github.com/nodejs/node/commit/ed3604cd64)] - **(SEMVER-MAJOR)** **http**: server check Host header, to meet RFC 7230 5.4 requirement (wwwzbwcom) [#45597](https://github.com/nodejs/node/pull/45597)
* \[[`88d71dc301`](https://github.com/nodejs/node/commit/88d71dc301)] - **(SEMVER-MAJOR)** **lib**: refactor to use min/max of `validateNumber` (Deokjin Kim) [#45772](https://github.com/nodejs/node/pull/45772)
* \[[`e4d641f02a`](https://github.com/nodejs/node/commit/e4d641f02a)] - **(SEMVER-MAJOR)** **lib**: refactor to use validators in http2 (Debadree Chatterjee) [#46174](https://github.com/nodejs/node/pull/46174)
* \[[`0f3e531096`](https://github.com/nodejs/node/commit/0f3e531096)] - **(SEMVER-MAJOR)** **lib**: performance improvement on readline async iterator (Thiago Oliveira Santos) [#41276](https://github.com/nodejs/node/pull/41276)
* \[[`5b5898ac86`](https://github.com/nodejs/node/commit/5b5898ac86)] - **(SEMVER-MAJOR)** **lib,src**: update exit codes as per todos (Debadree Chatterjee) [#45841](https://github.com/nodejs/node/pull/45841)
* \[[`2d0d99733b`](https://github.com/nodejs/node/commit/2d0d99733b)] - **(SEMVER-MAJOR)** **process**: remove `process.exit()`, `process.exitCode` coercion to integer (Daeyeon Jeong) [#43716](https://github.com/nodejs/node/pull/43716)
* \[[`dc06df31b6`](https://github.com/nodejs/node/commit/dc06df31b6)] - **(SEMVER-MAJOR)** **readline**: refactor to use `validateNumber` (Deokjin Kim) [#45801](https://github.com/nodejs/node/pull/45801)
* \[[`295b2f3ff4`](https://github.com/nodejs/node/commit/295b2f3ff4)] - **(SEMVER-MAJOR)** **src**: update NODE\_MODULE\_VERSION to 115 (Michaël Zasso) [#47251](https://github.com/nodejs/node/pull/47251)
* \[[`3803b028dd`](https://github.com/nodejs/node/commit/3803b028dd)] - **(SEMVER-MAJOR)** **src**: share common code paths for SEA and embedder script (Anna Henningsen) [#46825](https://github.com/nodejs/node/pull/46825)
* \[[`e8bddac3e9`](https://github.com/nodejs/node/commit/e8bddac3e9)] - **(SEMVER-MAJOR)** **src**: apply ABI-breaking API simplifications (Anna Henningsen) [#46705](https://github.com/nodejs/node/pull/46705)
* \[[`f84de0ad4c`](https://github.com/nodejs/node/commit/f84de0ad4c)] - **(SEMVER-MAJOR)** **src**: use uint32\_t for process initialization flags enum (Anna Henningsen) [#46427](https://github.com/nodejs/node/pull/46427)
* \[[`a6242772ec`](https://github.com/nodejs/node/commit/a6242772ec)] - **(SEMVER-MAJOR)** **src**: fix ArrayBuffer::Detach deprecation (Michaël Zasso) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`dd5c39a808`](https://github.com/nodejs/node/commit/dd5c39a808)] - **(SEMVER-MAJOR)** **src**: update NODE\_MODULE\_VERSION to 112 (Yagiz Nizipli) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`63eca7fec0`](https://github.com/nodejs/node/commit/63eca7fec0)] - **(SEMVER-MAJOR)** **stream**: validate readable defaultEncoding (Marco Ippolito) [#46430](https://github.com/nodejs/node/pull/46430)
* \[[`9e7093f416`](https://github.com/nodejs/node/commit/9e7093f416)] - **(SEMVER-MAJOR)** **stream**: validate writable defaultEncoding (Marco Ippolito) [#46322](https://github.com/nodejs/node/pull/46322)
* \[[`fb91ee4f26`](https://github.com/nodejs/node/commit/fb91ee4f26)] - **(SEMVER-MAJOR)** **test**: make trace-gc-flag tests less strict (Yagiz Nizipli) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`eca618071e`](https://github.com/nodejs/node/commit/eca618071e)] - **(SEMVER-MAJOR)** **test**: adapt test-v8-stats for V8 update (Michaël Zasso) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`c03354d3e0`](https://github.com/nodejs/node/commit/c03354d3e0)] - **(SEMVER-MAJOR)** **test**: test case for multiple res.writeHead and res.getHeader (Marco Ippolito) [#45508](https://github.com/nodejs/node/pull/45508)
* \[[`c733cc0c7f`](https://github.com/nodejs/node/commit/c733cc0c7f)] - **(SEMVER-MAJOR)** **test\_runner**: mark module as stable (Colin Ihrig) [#46983](https://github.com/nodejs/node/pull/46983)
* \[[`7ce223273d`](https://github.com/nodejs/node/commit/7ce223273d)] - **(SEMVER-MAJOR)** **tools**: update V8 gypfiles for 11.1 (Michaël Zasso) [#47251](https://github.com/nodejs/node/pull/47251)
* \[[`ca4bd3023e`](https://github.com/nodejs/node/commit/ca4bd3023e)] - **(SEMVER-MAJOR)** **tools**: update V8 gypfiles for 11.0 (Michaël Zasso) [#47251](https://github.com/nodejs/node/pull/47251)
* \[[`58b06a269a`](https://github.com/nodejs/node/commit/58b06a269a)] - **(SEMVER-MAJOR)** **tools**: update V8 gypfiles (Michaël Zasso) [#45579](https://github.com/nodejs/node/pull/45579)
* \[[`027841c964`](https://github.com/nodejs/node/commit/027841c964)] - **(SEMVER-MAJOR)** **url**: use private properties for brand check (Yagiz Nizipli) [#46904](https://github.com/nodejs/node/pull/46904)
* \[[`3bed5f11e0`](https://github.com/nodejs/node/commit/3bed5f11e0)] - **(SEMVER-MAJOR)** **url**: runtime-deprecate url.parse() with invalid ports (Rich Trott) [#45526](https://github.com/nodejs/node/pull/45526)
* \[[`7c76fddf25`](https://github.com/nodejs/node/commit/7c76fddf25)] - **(SEMVER-MAJOR)** **util,doc**: mark parseArgs() as stable (Colin Ihrig) [#46718](https://github.com/nodejs/node/pull/46718)

### Semver-Minor Commits

TBD

### Semver-Patch Commits

TBD
