project ('kfft', 'c',
         version: '0.5.1',
         license: 'Zlib',
         default_options:[
            'c_std=gnu11',
            'warning_level=2',
            'strip=true',
         ],
         subproject_dir: 'libs',
         meson_version: '>=0.52')

message ('Build configuration - @0@'.format(get_option('buildtype')))

kfft_ver = meson.project_version().split('.')

kfft_src = files('''
    kfft_main.c
'''.split())

cc = meson.get_compiler('c')
ccid = cc.get_id()
ccfam = target_machine.cpu_family()
osid = target_machine.system()

kfft_cflags  = '''
'''.split()

kfft_ldflags = '''
'''.split()

kfft_defs    = '''
'''.split()

kfft_deps = []

configure_file (
    output: 'config.h',
    configuration : {
        'VER_MAJOR': kfft_ver[0],
        'VER_MINOR': kfft_ver[1],
        'VER_PATCH': kfft_ver[2],
        
        'APP_NAME': '"' + meson.project_name() + '"',
    }
)

kfft_dep = dependency('kfft', version: '>=0.5.0',
  fallback: [ 'kfft', 'kfft_lib' ])

app_dep = [kfft_dep]
if not (osid == 'windows')
    app_dep += cc.find_library('dl', required: true)
endif
app_rpath = ':'.join ([
    '$ORIGIN'/'.',
    '$ORIGIN'/'..'
])

app_fft = executable (meson.project_name(), 'kfft_main.c',
                       dependencies: app_dep,
                       build_rpath: app_rpath,
                       install: true)
