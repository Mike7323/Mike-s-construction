import '../common/index.mjs';
import * as fixtures from '../common/fixtures.mjs';

import assert from 'assert';
import { readFileSync } from 'fs';

import * as html from '../../tools/doc/html.mjs';
import { replaceLinks } from '../../tools/doc/markdown.mjs';
import {
  rehypeRaw,
  rehypeStringify,
  remarkParse,
  remarkRehype,
  unified,
} from '../../tools/doc/deps.mjs';

// Test links mapper is an object of the following structure:
// {
//   [filename]: {
//     [link definition identifier]: [url to the linked resource]
//   }
// }
const testLinksMapper = {
  'foo': {
    'command line options': 'cli.html#cli-options',
    'web server': 'example.html',
  },
};

function toHTML({ input, filename, nodeVersion, versions }) {
  const content = unified()
    .use(replaceLinks, { filename, linksMapper: testLinksMapper })
    .use(remarkParse)
    .use(html.firstHeader)
    .use(html.preprocessText, { nodeVersion })
    .use(html.preprocessElements, { filename })
    .use(html.buildToc, { filename, apilinks: {} })
    .use(remarkRehype, { allowDangerousHtml: true })
    .use(rehypeRaw)
    .use(rehypeStringify)
    .processSync(input);

  return html.toHTML({ input, content, filename, nodeVersion, versions });
}

// Test data is a list of objects with two properties.
// The file property is the file path.
// The html property is some HTML which will be generated by the doctool.
// This HTML will be stripped of all whitespace because we don't currently
// have an HTML parser.
const testData = [
  {
    file: fixtures.path('order_of_end_tags_5873.md'),
    html: '<h4>Static method: Buffer.from(array) <span> ' +
      '<a class="mark" href="#static-method-bufferfromarray" ' +
      'id="static-method-bufferfromarray">#</a> </span> ' +
      '<a aria-hidden="true" class="legacy" ' +
      'id="foo_static_method_buffer_from_array"></a></h4>' +
      '<ul><li><code>array</code><a ' +
      'href="https://developer.mozilla.org/en-US/docs/Web/JavaScript/' +
      'Reference/Global_Objects/Array" class="type">&#x3C;Array></a></li></ul>',
  },
  {
    file: fixtures.path('doc_with_yaml.md'),
    html: '<h2>Sample Markdown with YAML info' +
      '<span><a class="mark" href="#sample-markdown-with-yaml-info" ' +
      ' id="sample-markdown-with-yaml-info">#</a></span>' +
      '<a aria-hidden="true" class="legacy" ' +
      'id="foo_sample_markdown_with_yaml_info"></a></h2>' +
      '<section><h3>Foobar<span><a class="mark" href="#foobar" ' +
      'id="foobar">#</a></span>' +
      '<a aria-hidden="true" class="legacy" id="foo_foobar"></a></h3>' +
      '<div class="api_metadata"><span>Added in: v1.0.0</span></div> ' +
      '<p>Describe <code>Foobar</code> in more detail here.</p>' +
      '</section><section>' +
      '<h3>Foobar II<span><a class="mark" href="#foobar-ii" ' +
      'id="foobar-ii">#</a></span>' +
      '<a aria-hidden="true" class="legacy" id="foo_foobar_ii"></a></h3>' +
      '<div class="api_metadata">' +
      '<details class="changelog"><summary>History</summary>' +
      '<table><tbody><tr><th>Version</th><th>Changes</th></tr>' +
      '<tr><td>v4.2.0</td><td><p>The <code>error</code> parameter can now be' +
      'an arrow function.</p></td></tr>' +
      '<tr><td>v5.3.0, v4.2.0</td>' +
      '<td><p><span>Added in: v5.3.0, v4.2.0</span></p></td></tr>' +
      '</tbody></table></details></div> ' +
      '<p>Describe <code>Foobar II</code> in more detail here.' +
      '<a href="http://man7.org/linux/man-pages/man1/fg.1.html"><code>fg(1)' +
      '</code></a></p></section><section>' +
      '<h3>Deprecated thingy<span><a class="mark" ' +
      'href="#deprecated-thingy" id="deprecated-thingy">#</a>' +
      '</span><a aria-hidden="true" class="legacy"' +
      'id="foo_deprecated_thingy"></a>' +
      '</h3><div class="api_metadata"><span>Added in: v1.0.0</span>' +
      '<span>Deprecated since: v2.0.0</span></div><p>Describe ' +
      '<code>Deprecated thingy</code> in more detail here.' +
      '<a href="http://man7.org/linux/man-pages/man1/fg.1p.html"><code>fg(1p)' +
      '</code></a></p></section><section>' +
      '<h3>Something<span><a class="mark" href="#something' +
      '" id="something">#</a></span>' +
      '<a aria-hidden="true" class="legacy" id="foo_something"></a></h3>' +
      '<!-- This is not a metadata comment --> ' +
      '<p>Describe <code>Something</code> in more detail here. </p></section>',
  },
  {
    file: fixtures.path('sample_document.md'),
    html: '<ol><li>fish</li><li>fish</li></ol>' +
      '<ul><li>Red fish</li><li>Blue fish</li></ul>',
  },
  {
    file: fixtures.path('altdocs.md'),
    html: '<li><a href="https://nodejs.org/docs/latest-v8.x/api/foo.html">8.x',
  },
  {
    file: fixtures.path('document_with_links.md'),
    html: '<h2>Usage and Example<span><a class="mark"' +
    'href="#usage-and-example" id="usage-and-example">#</a>' +
    '</span><a aria-hidden="true" class="legacy" id="foo_usage_and_example">' +
    '</a></h2><section><h3>Usage<span><a class="mark" href="#usage"' +
    'id="usage">#</a></span><a aria-hidden="true" class="legacy"' +
    'id="foo_usage"></a></h3><p><code>node \\[options\\] index.js' +
    '</code></p><p>Please see the<a href="cli.html#cli-options">' +
    'Command Line Options</a>document for more information.</p>' +
    '</section><section><h3>' +
    'Example<span><a class="mark" href="#example" id="example">' +
    '#</a></span><a aria-hidden="true" class="legacy" id="foo_example">' +
    '</a></h3><p>An example of a<a href="example.html">' +
    'webserver</a>written with Node.js which responds with<code>' +
    '\'Hello, World!\'</code>:</p></section><section>' +
    '<h3>See also<span><a class="mark"' +
    'href="#see-also" id="see-also">#</a></span><a aria-hidden="true"' +
    'class="legacy" id="foo_see_also"></a></h3><p>Check' +
    'out also<a href="https://nodejs.org/">this guide</a></p></section>',
  },
  {
    file: fixtures.path('document_with_special_heading.md'),
    html: '<title>Sample markdown with special heading |',
  },
  {
    file: fixtures.path('document_with_esm_and_cjs_code_snippet.md'),
    html: '<input class="js-flavor-selector" type="checkbox" checked',
  },
  {
    file: fixtures.path('document_with_cjs_and_esm_code_snippet.md'),
    html: '<input class="js-flavor-selector" type="checkbox" aria-label',
  },
];

const spaces = /\s/g;
const versions = [
  { num: '10.x', lts: true },
  { num: '9.x' },
  { num: '8.x' },
  { num: '7.x' },
  { num: '6.x' },
  { num: '5.x' },
  { num: '4.x' },
  { num: '0.12.x' },
  { num: '0.10.x' }];

testData.forEach(({ file, html }) => {
  // Normalize expected data by stripping whitespace.
  const expected = html.replace(spaces, '');

  const input = readFileSync(file, 'utf8');

  const output = toHTML({ input,
                          filename: 'foo',
                          nodeVersion: process.version,
                          versions });

  const actual = output.replace(spaces, '');
  // Assert that the input stripped of all whitespace contains the
  // expected markup.
  assert(actual.includes(expected),
         `ACTUAL: ${actual}\nEXPECTED: ${expected}`);
});
