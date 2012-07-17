#ifndef __LASER_POLZN_H__
#define __LASER_POLZN_H__ 1

#include <gsl/gsl_complex.h>

typedef struct laser_polzn_vec_t {
  gsl_complex (*get) (struct laser_polzn_vect_t *e, const int p);
  void (*set) (struct laser_polzn_vec_t *e, const int p, gsl_complex val);
  void (*rotate) (struct laser_polzn_vec_t *e, const int p, 
		  const double phi, const double theta, const double chi);
  gsl_complex e[3];
} laser_polzn_vec;

void laser_polzn_vec_init_from_cart (laser_polzn_vec *e, const gsl_complex ex,
				     const gsl_complex ey, const gsl_complex ez);


gsl_complex laser_polzn_vec_get (const laser_polzn_vec *e, const int p);

void laser_polzn_vec_free (laser_polzn_vec *e);

laser_polzn_vec laser_polzn_vec_rotate (const laser_polzn_vec e,
					const double phi,
					const double theta,
					const double chi);

typedef struct laser_polzn_tensor
{
  gsl_complex (*get) (struct laser_polzn_vec_t *e, const int p);
  void (*set) (struct laser_polzn_vec_t *e, const int p, gsl_complex val);
  gsl_complex E[9];
} laser_polzn_tensor;

laser_polzn_tensor laser_polzn_tensor_calc (const laser_polzn_vec e1,
					    const laser_polzn_vec e2);

gsl_complex laser_polzn_tensor_get (const laser_polzn_tensor E,
				    const int k, const int p);

void laser_polzn_tensor_free (laser_polzn_tensor * E);

#endif /* __LASER_POLZN_H__ */
