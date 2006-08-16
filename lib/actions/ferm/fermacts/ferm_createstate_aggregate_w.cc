// $Id: ferm_createstate_aggregate_w.cc,v 3.2 2006-08-16 17:10:26 bjoo Exp $
/*! \file
 *  \brief All ferm create-state method
 */

#include "chromabase.h"

#include "actions/ferm/fermacts/ferm_createstate_aggregate_w.h"
#include "actions/ferm/fermacts/simple_fermstate_w.h"
#include "actions/ferm/fermacts/stout_fermstate_w.h"

namespace Chroma
{

  //! Registration aggregator
  namespace CreateFermStateEnv
  {
    bool registerAll() 
    {
      bool success = true;

      success &= CreateSimpleFermStateEnv::registered;
      success &= CreateStoutFermStateEnv::registered;
      success &= CreateSLICFermStateEnv::registered;

      return success;
    }

    const bool registered = registerAll();
  }

}
