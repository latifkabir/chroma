// -*- C++ -*-
// $Id: unprec_wilson_fermact_w.h,v 1.14 2003-12-15 17:52:51 bjoo Exp $
/*! \file
 *  \brief Unpreconditioned Wilson fermion action
 */

#ifndef __unprec_wilson_fermact_w_h__
#define __unprec_wilson_fermact_w_h__

#include "fermact.h"
#include "actions/ferm/linop/unprec_wilson_linop_w.h"

using namespace QDP;

//! Unpreconditioned Wilson fermion action
/*! \ingroup fermact
 *
 * Supports creation and application for fermion actions
 */

class UnprecWilsonFermAct : public UnprecWilsonTypeFermAct<LatticeFermion>
{
public:
  //! Partial constructor
  UnprecWilsonFermAct() {}

  //! Full constructor
  UnprecWilsonFermAct(const Real& _Mass)
    {create(_Mass);}

  //! Creation routine
  void create(const Real& _Mass);

  //! Produce a linear operator for this action
  const LinearOperator<LatticeFermion>* linOp(const ConnectState& state) const;

  //! Produce a linear operator M^dag.M for this action
  const LinearOperator<LatticeFermion>* lMdagM(const ConnectState& state) const;

  //! Compute dS_f/dU
  void dsdu(multi1d<LatticeColorMatrix>& result,
	    const ConnectState& state,
	    const LatticeFermion& psi) const;

  //! Destructor is automatic
  ~UnprecWilsonFermAct() {}

private:
  Real Mass;
  UnprecWilsonLinOp D;
};

#endif
