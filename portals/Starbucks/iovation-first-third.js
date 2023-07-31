/*
 Copyright(c) 2017, iovation, inc. All rights reserved.
*/
(function A() {
  function u(a, b) {
    var d = {},
      c;
    for (c = a.length - 1; -1 < c; c--)
      0 < c
        ? (d[c] = (function () {
            var g = c;
            return function () {
              return v(a[g], d[g + 1], b);
            };
          })())
        : v(a[c], d[c + 1], b);
  }
  function v(f, m, d) {
    var c = document.createElement('script'),
      g = f[0].split('?')[0].split('/'),
      e;
    e = g[g.length - 1].split('.')[0];
    g = (a[d] && a[d].staticVer && a[d].staticVer + '/') || f[1];
    /([0-9]+\.){2}[0-9]+\//.test(f[1]) &&
      g !== f[1] &&
      h('loader: Overriding configured version with staticVer.');
    f[0] = f[0].replace('##version##', g);
    c.setAttribute('src', f[0]);
    c && c.addEventListener
      ? c.addEventListener('error', function () {
          b[d + '_' + e + '_load_failure'] = 'true';
        })
      : c.attachEvent &&
        c.attachEvent('onerror', function () {
          b[d + '_' + e + '_load_failure'] = 'true';
        });
    m && (c.onload = m);
    document.getElementsByTagName('head')[0].appendChild(c);
  }
  function h(b) {
    if ('function' === typeof a.trace_handler)
      try {
        a.trace_handler(b);
      } catch (e) {}
  }
  function e(a, b) {
    var d = null !== a && void 0 !== a;
    return !d || ('1' !== a.toString() && 'true' !== a.toString().toLowerCase())
      ? !d || ('0' !== a.toString() && 'false' !== a.toString().toLowerCase())
        ? 'boolean' === typeof b
          ? b
          : !1
        : !1
      : !0;
  }
  var t = window,
    w = t.io_global_object_name || 'IGLOO',
    a = (t[w] = t[w] || {}),
    b = (a.loader = a.loader || {}),
    x = [],
    y = [];
  if (b.loaderMain)
    return (
      h(
        "loader: Loader script has already run, try reducing the number of places it's being included."
      ),
      !1
    );
  b.loaderMain = A;
  b.loaderVer = '5.1.0';
  (function () {
    var f = e(b.tp, !0),
      m = e(b.fp_static, !0),
      d = e(b.fp_dyn, !0),
      c = e(b.enable_legacy_compatibility),
      g = e(b.tp_split),
      u =
        (b.tp_host && b.tp_host.replace(/\/+$/, '')) ||
        'https://mpsnare.iesnare.com',
      z = b.fp_static_override_uri,
      l = void 0 !== b.uri_hook ? b.uri_hook + '/' : '/iojs/',
      n = (b.version || 'versionOrAliasIsRequired') + '/',
      v = b.subkey ? t.encodeURIComponent(b.subkey) + '/' : '',
      w = b.tp_resource || 'wdp.js',
      p = b.tp_host ? '&tp_host=' + t.encodeURIComponent(b.tp_host) : '',
      B = z ? '&fp_static_uri=' + t.encodeURIComponent(z) : '',
      q,
      r,
      k;
    b.tp_host = u;
    q = e(a.enable_flash, !0);
    r = a.io && a.io.enable_flash;
    k = a.fp && a.fp.enable_flash;
    r = void 0 !== r && null !== r ? e(r, !0) : q;
    void 0 !== k && null !== k ? (k = e(k, !0)) : (r = q);
    q = r ? '&flash=true' : '&flash=false';
    k = k ? '&flash=true' : '&flash=false';
    p =
      '?loaderVer=' +
      b.loaderVer +
      '&compat=' +
      c +
      '&tp=' +
      f +
      '&tp_split=' +
      g +
      p +
      '&fp_static=' +
      m +
      '&fp_dyn=' +
      d +
      B;
    f ||
      m ||
      h('loader: Not currently configured to load fp_static or tp script(s).');
    a.fp &&
      a.fp.staticVer &&
      a.fp.staticVer + '/' !== n &&
      ((n = a.fp.staticVer + '/'),
      h(
        'loader: Configured version replaced with that from pre-loaded static script.'
      ));
    m || (a.fp && a.fp.staticMain)
      ? ((l = (l + '##version##' + v).replace(/\/\//g, '/')),
        m &&
          (a.fp && a.fp.staticMain
            ? c &&
              !a.fp.preCompatMain &&
              h(
                'loader: enable_legacy_compatibility on, but included static does not have the compat wrapper.'
              )
            : z
            ? x.push([z, ''])
            : x.push([l + 'static_wdp.js' + p + k, n])),
        !d || (a.fp && a.fp.dynMain)
          ? a.fp &&
            a.fp.dynMain &&
            h(
              "loader: First party dynamic script has already been loaded, disable fp_dyn or make sure you're not manually including the dynamic file separately."
            )
          : x.push([l + 'dyn_wdp.js' + p + k, n]))
      : e(b.fp_dyn) &&
        h(
          'loader: Invalid Config, first party dynamic script set to load without static.'
        );
    f &&
      (a.io && a.io.staticMain
        ? h('loader: Third party script has already been loaded.')
        : ((l = u + '/##version##' + v),
          g
            ? (y.push([l + 'static_wdp.js' + p + q, n]),
              y.push([l + 'dyn_wdp.js' + p + q, n]),
              b.tp_resource &&
                h(
                  'loader: Invalid Config: both tp_resource and tp_split set. Ignoring tp_resource.'
                ))
            : y.push([l + w + p + q, n])));
  })();
  u(x, 'fp');
  u(y, 'io');
})();
