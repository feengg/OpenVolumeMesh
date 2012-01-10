#ifndef INCLUDE_UNITTESTS_COMMON_HH
#define INCLUDE_UNITTESTS_COMMON_HH

#include <gtest/gtest.h>
#include <OpenMesh/Core/IO/MeshIO.hh>

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

struct CustomTraits : public OpenMesh::DefaultTraits {
};

typedef OpenMesh::TriMesh_ArrayKernelT<CustomTraits> Mesh;

/*
 * Simple test setting.
 */

class OpenMeshBase : public testing::Test {

    protected:

        // This function is called before each test is run
        virtual void SetUp() {
            
            // Do some initial stuff with the member data here...
        }

        // This function is called after all tests are through
        virtual void TearDown() {

            // Do some final stuff with the member data here...
        }

    // This member will be accessible in all tests
    Mesh mesh_;  
};

#endif // INCLUDE GUARD
