// Copyright 2021 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Flags: --harmony-temporal

d8.file.execute('test/mjsunit/temporal/temporal-helpers.js');

let d1 = new Temporal.PlainDateTime(2021, 12, 11, 1,2,3,4,5,6);
let badDateTime = { toPlainMonthDay: d1.toPlainMonthDay }
assertThrows(() => badDateTime.toPlainMonthDay(), TypeError);

assertPlainMonthDay(d1.toPlainMonthDay(), "M12", 11);
