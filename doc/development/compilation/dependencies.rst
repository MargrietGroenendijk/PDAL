.. _dependencies:

==============================================================================
Dependencies
==============================================================================


.. note::

    The absolute best source of build and configuration examples is the
    PDAL GitHub repository. Specifically, the continuous integration
    scripts at https://github.com/PDAL/PDAL/tree/master/scripts/ci

PDAL depends on a number of libraries to do its work.  You should make sure
those dependencies are installed on your system before installing PDAL
or use a packaging system that will automatically ensure that prerequisites
are satisified.  Packaging system such as `apt`_ or `Conda`_ can
be used to install dependencies on your system.

.. _`apt`: https://help.ubuntu.com/lts/serverguide/apt.html
.. _`Conda`: https://conda.io/en/latest/

Required Dependencies
------------------------------------------------------------------------------

GDAL (2.2+)
..............................................................................

PDAL uses GDAL for spatial reference system description manipulation, and image
reading supporting for the NITF driver. In
conjunction with GeoTIFF_, GDAL is used to convert GeoTIFF keys and OGC WKT SRS
description strings into formats required by specific drivers.  ::

    Source: https://github.com/OSGeo/gdal
    Conda: https://anaconda.org/conda-forge/gdal

GeoTIFF (1.3+)
..............................................................................

PDAL uses GeoTIFF in conjunction with GDAL for GeoTIFF key support in the
LAS driver.  GeoTIFF is typically a dependency of GDAL, so installing GDAL
from a package will generally install GeoTIFF as well. ::

    Source: https://github.com/OSGeo/libgeotiff
    Conda: https://anaconda.org/conda-forge/geotiff

.. note::
    `GDAL` surreptitiously embeds a copy of `GeoTIFF`_ in its library build
    but there is no way for you to know this.  In addition to embedding
    libgeotiff, it also strips away the library symbols that PDAL needs,
    meaning that PDAL can't simply link against `GDAL`_.  If you are
    building both of these libraries yourself, make sure you build GDAL
    using the "External libgeotiff" option, which will prevent the
    insanity that can ensue on some platforms.  `Conda Forge`_ users, including
    those using that platform to link and build PDAL themselves, do
    not need to worry about this issue.

Optional Dependencies
------------------------------------------------------------------------------

LASzip (Latest package/source recommended)
..............................................................................

`LASzip`_ is a library with a `CMake`-based build system that
provides periodic compression of `ASPRS LAS`_ data. It is used by the
:ref:`writers.las` and :ref:`readers.las` to provide
compressed LAS support.::

    Source: https://github.com/LASzip/LASzip
    Conda: https://anaconda.org/conda-forge/laszip

laz-perf (Latest package/source recommended)
..............................................................................

laz-perf provides an alternative LAS compression/decompression engine that
may be slightly faster in some circumstances.  laz-perf supports fewer LAS
point types and versions than does LASzip.

    Source: https://github.com/verma/laz-perf/
    Conda: https://anaconda.org/conda-forge/laz-perf

libxml2  (2.7+)
..............................................................................

libxml2_ is used to serialize PDAL dimension descriptions into XML for
:ref:`readers.pgpointcloud`.::

    Source: http://www.xmlsoft.org/
    Conda: https://anaconda.org/conda-forge/libxml2

Plugin Dependencies
------------------------------------------------------------------------------

PDAL comes with optional plugin stages that require other libraries in order
to run.  Many of these libraries are licensed in a way incompatible with
the PDAL license or they may be commercial products that require purchase.

Nitro (Requires specific source package)
..............................................................................

Nitro is a library that provides `NITF`_ support for PDAL to write LAS-in-NITF
files for :ref:`writers.nitf`.  You must use the specific version of Nitro
referenced below for licensing and compatibility reasons.::

    Source: http://github.com/hobu/nitro

TileDB  (1.4.1+)
..............................................................................

`TileDB`_ is an efficient multi-dimensional array management system which
introduces a novel on-disk format that can effectively store dense and sparse
array data with support for fast updates and reads. It features excellent
compression, and an efficient parallel I/O system with high scalability. It is
used by :ref:`writers.tiledb` and :ref:`readers.tiledb`.::

    Source: https://github.com/TileDB-Inc/TileDB
    Conda: https://anaconda.org/conda-forge/tiledb

.. _`ASPRS LAS`: http://www.asprs.org/Committee-General/LASer-LAS-File-Format-Exchange-Activities.html
.. _`LASzip`: http://laszip.org
.. _`NITF`: http://en.wikipedia.org/wiki/National_Imagery_Transmission_Format
.. _`Nitro`: http://nitro-nitf.sourceforge.net/wikka.php?wakka=HomePage
.. _`DebianGIS`: http://wiki.debian.org/DebianGis
.. _`Debian`: http://www.debian.org
.. _`Conda Forge`: https://anaconda.org/conda-forge/pdal

.. _GDAL: http://www.gdal.org
.. _GeoTIFF: http://trac.osgeo.org/geotiff
.. _libxml2: http://xmlsoft.org
.. _CMake: http://www.cmake.org
.. _`Point Cloud Library (PCL)`: http://pointclouds.org
.. _`TileDB`: https://www.tiledb.io
