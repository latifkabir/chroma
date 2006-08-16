// -*- C++ -*-
// $Id: prec_slic_linop_w.h,v 1.1 2006-08-16 17:10:27 bjoo Exp $
/*! \file
 *  \brief Even-odd preconditioned Clover fermion linear operator
 */

#ifndef __prec_slic_linop_w_h__
#define __prec_slic_linop_w_h__

#include "state.h"
#include "fermbc.h"
#include "prec_logdet_linop.h"
#include "actions/ferm/fermacts/clover_fermact_params_w.h"
#include "actions/ferm/linop/dslash_w.h"
#include "actions/ferm/linop/clover_term_w.h"
#include "actions/ferm/fermacts/stout_fermstate_w.h"
#include "actions/ferm/fermacts/simple_fermstate.h"


namespace Chroma 
{ 
  //! Even-odd preconditioned SLIC-Dirac operator
  /*!
   * \ingroup linop
   *
   * This routine is specific to Wilson fermions!
   *
   * The kernel for SLIC fermions is
   *
   *      M  =  A + (d+M) - (1/2) D'
   */
  class EvenOddPrecSLICLinOp : public EvenOddPrecLogDetLinearOperator<LatticeFermion, 
				 multi1d<LatticeColorMatrix>, multi1d<LatticeColorMatrix> >
  {
  public:
    // Typedefs to save typing
    typedef LatticeFermion               T;
    typedef multi1d<LatticeColorMatrix>  P;
    typedef multi1d<LatticeColorMatrix>  Q;

    //! Partial constructor
    EvenOddPrecSLICLinOp() {}

    //! Full constructor
    EvenOddPrecSLICLinOp(Handle< FermState<T,P,Q> > fs,
			 const CloverFermActParams& param_) : slic_fs(fs)
      {create(fs, param_);}

    //! Destructor is automatic
    ~EvenOddPrecSLICLinOp() {}

    //! Return the fermion BC object for this linear operator
    const FermBC<T,P,Q>& getFermBC() const {return D.getFermBC();}

    //! Creation routine
    void create(Handle< FermState<T,P,Q> > fs,
		const CloverFermActParams& param_);

    //! Apply the the even-even block onto a source vector
    void evenEvenLinOp(LatticeFermion& chi, const LatticeFermion& psi, 
		       enum PlusMinus isign) const;

    //! Apply the inverse of the even-even block onto a source vector
    void evenEvenInvLinOp(LatticeFermion& chi, const LatticeFermion& psi, 
			  enum PlusMinus isign) const;
  
    //! Apply the the even-odd block onto a source vector
    void evenOddLinOp(LatticeFermion& chi, const LatticeFermion& psi, 
		      enum PlusMinus isign) const;

    //! Apply the the odd-even block onto a source vector
    void oddEvenLinOp(LatticeFermion& chi, const LatticeFermion& psi, 
		      enum PlusMinus isign) const;

    //! Apply the the odd-odd block onto a source vector
    void oddOddLinOp(LatticeFermion& chi, const LatticeFermion& psi, 
		     enum PlusMinus isign) const;

    // Override inherited one with a few more funkies
    void operator()(LatticeFermion& chi, const LatticeFermion& psi, 
		    enum PlusMinus isign) const;

    //! Apply the even-even block onto a source vector
    void derivEvenEvenLinOp(multi1d<LatticeColorMatrix>& ds_u, 
			    const LatticeFermion& chi, const LatticeFermion& psi, 
			    enum PlusMinus isign) const;

    void derivEvenEvenLogDet(multi1d<LatticeColorMatrix>& ds_u, 
			     enum PlusMinus isign) const;

    //! Apply the the even-odd block onto a source vector
    void derivEvenOddLinOp(multi1d<LatticeColorMatrix>& ds_u, 
			   const LatticeFermion& chi, const LatticeFermion& psi, 
			   enum PlusMinus isign) const;
 
    //! Apply the the odd-even block onto a source vector
    void derivOddEvenLinOp(multi1d<LatticeColorMatrix>& ds_u, 
			   const LatticeFermion& chi, const LatticeFermion& psi, 
			   enum PlusMinus isign) const;

    //! Apply the the odd-odd block onto a source vector
    void derivOddOddLinOp(multi1d<LatticeColorMatrix>& ds_u, 
			  const LatticeFermion& chi, const LatticeFermion& psi, 
			  enum PlusMinus isign) const;

    //! Return flops performed by the operator()
    unsigned long nFlops() const;

    //! Get the log det of the even even part
    Double LogDetEvenEven(void) const ; 

  private:
    Handle< FermState<T,P,Q> > slic_fs;
    Handle< SimpleFermState<T,P,Q> > thin_fs;
    CloverFermActParams param;
    WilsonDslash D;
    CloverTerm   clov;
    CloverTerm   invclov;  // uggh, only needed for evenEvenLinOp
  };

} // End Namespace Chroma


#endif
