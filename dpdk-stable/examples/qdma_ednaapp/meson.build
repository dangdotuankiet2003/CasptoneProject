project('my_dpdk_app', 'c',
  version : '1.0',
  default_options : ['warning_level=2', 'c_std=gnu11'])

dpdk = dependency('libdpdk', required: true)

executable('my_dpdk_app',
  'main.c',
  dependencies: dpdk,
  install: false)
