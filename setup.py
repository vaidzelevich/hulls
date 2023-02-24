import subprocess
import sys
from pathlib import Path
from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name: str, sourcedir: str = ''):
        super().__init__(name, sources=[])
        self.sourcedir = str(Path(sourcedir).resolve())


class CMakeBuild(build_ext):
    def build_extension(self, ext: CMakeExtension) -> None:
        extdir = Path(self.get_ext_fullpath(ext.name)).resolve().parent
        cmake_args = [f'-DPYTHON_EXECUTABLE={sys.executable}']
        build_args = []
        if self.compiler.compiler_type == 'msvc':
            cmake_args += [
                f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE={extdir}']
            build_args += ['--config', 'Release']
        else:
            cmake_args += [
                f'-DCMAKE_BUILD_TYPE=Release',
                f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}'
            ]

        build_temp = Path(self.build_temp) / ext.name
        build_temp.mkdir(parents=True, exist_ok=True)

        subprocess.run(['cmake', ext.sourcedir, *cmake_args],
                       cwd=build_temp, check=True)
        subprocess.run(['cmake', '--build', '.', *build_args],
                       cwd=build_temp, check=True)


setup(
    name='hulls',
    ext_modules=[CMakeExtension('hulls')],
    cmdclass={'build_ext': CMakeBuild}
)
