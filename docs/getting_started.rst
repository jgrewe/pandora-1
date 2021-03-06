Introduction to *NIX*
=====================

This introduction guides through the *NIX*
data model and shows how to use it with the `nix c++
library <https://github.com/g-node/nix>`__.

For python we assembled `tutorials
<https://nixpy.readthedocs.io/en/latest/tutorial.html>`__ and `demos
<https://github.com/g-node/nix-demo>`__ using (`nixpy
<https://github.com/g-node/nixpy>`__).

---------------

In the following we provide an introduction to the general concepts of
the *NIX* data model, try to illustrate its design principles and
provide code examples showing the usage of the
`c++ <https://github.com/g-node/nix>`__ library for reading and writing
*NIX* files.

Code examples use the c++ library but almost all functions have direct
counterparts in the `python library <https://github.com/g-node/nixpy>`__
or the language bindings for
`Matlab <https://github.com/g-node/nix-mx>`__ and
`java <https://github.com/g-node/nix-java>`__.

Basic idea
==========

The basic idea of the *NIX* project is to come up with a **generic**
data model that defines as few structures/entities as possible while
being able to represent a multitude of different data structures, allows
for in-depth annotation and supports standardization.

Designing a **generic** data model implies that the defined entities are
named in a way that may seem uncommon but are more general than the
*domain-specific* terms used in any given field or community.

The idea of the *NIX* data model has been implemented using the
`HDF5 <https://www.hdfgroup.org>`__ file format.

---------

Tutorials
=========

Most code examples are standalone and
should readily build and run (:doc:`See these instructions<example_guide>`
if you need help on how to build and run them).

.. toctree::
   storing_data
   data_handling
   tagging
   annotating
   standardization
   file_handling
   finding_things
   :maxdepth: 1

.. toctree::
   example_guide
   :maxdepth: 1
