'use strict'

const common = require('../../common');

const assert = require('assert');
const fs = require('fs');
const path = require('path');

const readOnlyFolder = process.env.READONLYFOLDER;
const readWriteFolder = process.env.READWRITEFOLDER;
const writeOnlyFolder = process.env.WRITEONLYFOLDER;

{
  assert.ok(!process.permission.has('fs.write', readOnlyFolder));
  assert.ok(!process.permission.has('fs.read', writeOnlyFolder));
  assert.ok(process.permission.has('fs.write', readWriteFolder));

  assert.ok(process.permission.has('fs.write', writeOnlyFolder));
  assert.ok(process.permission.has('fs.read', readOnlyFolder));
  assert.ok(process.permission.has('fs.read', readWriteFolder));
}

{
  // App won't be able to symlink from a readOnlyFolder
  assert.throws(() => {
    fs.symlink(path.join(readOnlyFolder, 'file'), path.join(readWriteFolder, 'link-to-read-only'), 'file', (err) => {
      assert.ifError(err);
    });
  }, common.expectsError({
    code: 'ERR_ACCESS_DENIED',
    permission: 'FileSystemWrite',
    resource: path.toNamespacedPath(path.join(readOnlyFolder, 'file')),
  }));

  // App will be able to symlink to a writeOnlyFolder
  fs.symlink(path.join(readWriteFolder, 'file'), path.join(writeOnlyFolder, 'link-to-read-write'), 'file', (err) => {
    assert.ifError(err);
    // App will won't be able to read the symlink
    assert.throws(() => {
      fs.readFile(path.join(writeOnlyFolder, 'link-to-read-write'), (err) => {
        assert.ifError(err);
      });
    }, common.expectsError({
      code: 'ERR_ACCESS_DENIED',
      permission: 'FileSystemRead',
    }));

    // App will be able to write to the symlink
    fs.writeFile(path.join(writeOnlyFolder, 'link-to-read-write'), 'some content', common.mustSucceed());
  });

  // App won't be able to symlink to a readOnlyFolder
  assert.throws(() => {
    fs.symlink(path.join(readWriteFolder, 'file'), path.join(readOnlyFolder, 'link-to-read-only'), 'file', (err) => {
      assert.ifError(err);
    });
  }, common.expectsError({
    code: 'ERR_ACCESS_DENIED',
    permission: 'FileSystemWrite',
    resource: path.toNamespacedPath(path.join(readOnlyFolder, 'link-to-read-only')),
  }));
}
