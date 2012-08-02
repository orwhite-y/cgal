// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : odt_optimize_mesh_3 function definition.
//******************************************************************************

#ifndef CGAL_ODT_OPTIMIZE_MESH_3_H
#define CGAL_ODT_OPTIMIZE_MESH_3_H


#include <CGAL/Mesh_3/global_parameters.h>
#include <CGAL/Mesh_3/Mesh_global_optimizer.h>
#include <CGAL/Mesh_3/Odt_move.h>
#include <CGAL/Mesh_3/Mesh_sizing_field.h>
#include <CGAL/Mesh_optimization_return_code.h>
#include <CGAL/Mesh_3/parameters_defaults.h>

namespace CGAL {
  
#ifdef CGAL_FREEZE_VERTICES
BOOST_PARAMETER_FUNCTION(
  (Mesh_optimization_return_code),
  odt_optimize_mesh_3,
  parameters::tag,
  (required (in_out(c3t3),*) (domain,*) )
  (optional
    (time_limit_, *, 0 )
    (max_iteration_number_, *, 0 )
    (convergence_, *, parameters::default_values::odt_convergence_ratio )
    (freeze_bound_, *, parameters::default_values::odt_freeze_ratio )
    (do_freeze_, *, parameters::default_values::do_freeze ))
)
#else
BOOST_PARAMETER_FUNCTION(
  (Mesh_optimization_return_code),
  odt_optimize_mesh_3,
  parameters::tag,
  (required (in_out(c3t3),*) (domain,*) )
  (optional
    (time_limit_, *, 0 )
    (max_iteration_number_, *, 0 )
    (convergence_, *, parameters::default_values::odt_convergence_ratio )
    (freeze_bound_, *, parameters::default_values::odt_freeze_ratio )
  )
)
#endif
{
  return odt_optimize_mesh_3_impl(c3t3, domain,
                                  time_limit_, max_iteration_number_,
                                  convergence_, freeze_bound_
#ifdef CGAL_FREEZE_VERTICES
                                  , do_freeze_
#endif
                                  );
} 



template <typename C3T3, typename MeshDomain> 
Mesh_optimization_return_code
odt_optimize_mesh_3_impl(C3T3& c3t3,
                         const MeshDomain& domain,
                         const double time_limit,
                         std::size_t max_iteration_number,
                         const double convergence,
                         const double freeze_ratio
#ifdef CGAL_FREEZE_VERTICES 
                         , const bool do_freeze
#endif
                         )
{
  typedef typename C3T3::Triangulation  Tr;
  
  typedef Mesh_3::Mesh_sizing_field<Tr>             Sizing;
  typedef typename Mesh_3::Odt_move<C3T3,Sizing>    Move;
  
  typedef typename
    Mesh_3::Mesh_global_optimizer<C3T3,MeshDomain,Move> Odt_optimizer;

  // Create optimizer
  Odt_optimizer opt(c3t3,
                    domain,
                    freeze_ratio,
#ifdef CGAL_FREEZE_VERTICES
                    do_freeze,
#endif
                    convergence);
  
  // Set max time
  opt.set_time_limit(time_limit);
  
  // 1000 iteration max to avoid infinite loops
  if ( 0 == max_iteration_number )
    max_iteration_number = 1000;
  
  // Launch optimization
  return opt(static_cast<int>(max_iteration_number));
}

}  // end namespace CGAL


#endif // CGAL_ODT_OPTIMIZE_MESH_3_H
