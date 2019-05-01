#include "example.h"
#include <iostream>

int main() {
  pyne::MaterialLibrary mat_lib = pyne::MaterialLibrary("../full_lib.h5m");

  std::cout << "print list of available materials" << std::endl;
  for ( auto mat_name : mat_lib.get_matlist()) {
    std::cout << mat_name << std::endl;
  }
  std::cout << mat_lib.get_matlist().size() << std::endl;
  // get a material from the library 
   //pyne::Material my_mat1 = mat_lib.get_material("pyne::Photographic Emulsion, Standard Nuclear");
   //pyne::Material my_mat2 = mat_lib.get_material("G4_NIST::G4_URANIUM_DICARBIDE");
   //pyne::MaterialLibrary my_sim_mat_lib = pyne::MaterialLibrary();
   //my_sim_mat_lib.add_material(my_mat1);
   //my_sim_mat_lib.add_material(my_mat2);
  //std::cout << std::endl << std::endl << std::endl;
  //std::cout << "print a PHITS material input deck" << std::endl << std::endl;
  // Print the Materials
  //std::cout << my_mat1.phits() << std::endl;
  //std::cout << my_mat2.phits() << std::endl;
  
  //double frac1 = 0.232;
  //double frac2 = 0.09;
  //pyne::Material my_mat3 = my_mat1*frac1 + my_mat2*frac2;
  //my_mat3.metadata["name"] = "my_mix";
  //my_sim_mat_lib.add_material(my_mat3);
//  
//  std::cout << std::endl << std::endl << std::endl;
//  std::cout << "print a GDML material input deck" << std::endl <<std::endl;
//  // Print the isotopes present in the MaterialLibrary
    //std::cout << my_sim_mat_lib.gdml_isotopes() << std::endl;
//  
//  // Print the Materials
//  std::cout << my_mat1.gdml() << std::endl;
//  std::cout << my_mat2.gdml() << std::endl;
//
  //std::cout << my_sim_mat_lib.get_material("my_mix").gdml() << std::endl;


  std::ofstream file;
  file.open("full_mat_lib.gdml");
  file << mat_lib.gdml_isotopes();
  for ( auto mat_name : mat_lib.get_matlist()) {
    file << std::endl << std::endl;
    file << mat_lib.get_material(mat_name).gdml();    
  }

}
