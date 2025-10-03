#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum {
    STATUS_OK,
    STATUS_INVALID_EPS,
    STATUS_NO_LIM,
    STATUS_INVALID_CHOICE,
} Status;

Status e_ryad(double eps, double *e);
Status e_lim(double eps, double *e);
Status e_newton(double eps, double *e);

Status pi_ryad(double eps, double *pi);
Status pi_lim(double eps, double *pi);
Status pi_newton(double eps, double *pi);

Status ln2_ryad(double eps, double *ln2);
Status ln2_lim(double eps, double *ln2);
Status ln2_newton(double eps, double *ln2);

Status sqrt2_ryad(double eps, double *sqrt2);
Status sqrt2_lim(double eps, double *sqrt2);
Status sqrt2_newton(double eps, double *sqrt2);

Status y_ryad(double eps, double *y);
Status y_lim(double eps, double *y);
Status y_newton(double eps, double *y);
#endif