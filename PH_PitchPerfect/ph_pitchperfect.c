/**
 * @file ph_pitchperfect.c
 *An Pure Data Object to create frequency-values of Chords depending on the keynote
 *
 * @author Hannes Hügel and Michael Pohn<br>
 * Audiocommunication Group, Technical University Berlin
 *
 */


#include "m_pd.h"

static t_class *ph_pitchperfect_class;

/**
 *struct to define Inlets and Outlets of PD-Object
 *
 */

typedef struct ph_pitchperfect {
  t_object  x_obj;                  /**< Necessary for every signal object in Pure Data*/

  t_float input;                    /**< gets the value of the keynote */

  t_outlet *out_stage_1;            /**< basenote of the first harmonic chord */
  t_outlet *out_stage_1_3;          /**< third (to the basenote) of the first harmonic chord */
  t_outlet *out_stage_1_5;          /**< fifth (to the basenote) of the first harmonic chord */

  t_outlet *out_stage_2;            /**< basenote of the second harmonic chord */
  t_outlet *out_stage_2_3;          /**< third of the second harmonic chord */
  t_outlet *out_stage_2_5;          /**< fifth  of the second harmonic chord */

  t_outlet *out_stage_3;            /**< basenote of the third harmonic chord */
  t_outlet *out_stage_3_3;          /**< third of the third harmonic chord */
  t_outlet *out_stage_3_5;          /**< fifth  of the third harmonic chord */

  t_outlet *out_stage_4;            /**< basenote of the fourth harmonic chord */
  t_outlet *out_stage_4_3;          /**< third of the fourth harmonic chord */
  t_outlet *out_stage_4_5;          /**< fifth  of the fourth harmonic chord */

  t_outlet *out_stage_5;            /**< basenote of the fifth harmonic chord */
  t_outlet *out_stage_5_3;          /**< third of the fifth harmonic chord */
  t_outlet *out_stage_5_5;          /**< fifth  of the fifth harmonic chord */

  t_outlet *out_stage_6;            /**< basenote of the sixth harmonic chord */
  t_outlet *out_stage_6_3;          /**< third of the sixth harmonic chord */
  t_outlet *out_stage_6_5;          /**< fifth  of the sixth harmonic chord */

  t_outlet *out_stage_7;            /**< basenote of the seventh harmonic chord */
  t_outlet *out_stage_7_3;          /**< third of the seventh harmonic chord */
  t_outlet *out_stage_7_5;          /**< fifth  of the seventh harmonic chord */

  t_outlet *out_stage_8;            /**< basenote of the eighth harmonic chord */
  t_outlet *out_stage_8_3;          /**< third of the eighth harmonic chord */
  t_outlet *out_stage_8_5;          /**< fifth  of the eighth harmonic chord */

} ph_pitchperfect;



/**
 * this is the "constructor" of the class.
 * this method is called whenever a new object of this class is created.
 * Creates the Inlet and the  Outlets
 */
void *ph_pitchperfect_new()
{

	ph_pitchperfect *x = (ph_pitchperfect *)pd_new(ph_pitchperfect_class);

	x->out_stage_1 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_1_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_1_5 = outlet_new(&x->x_obj, &s_float);

	x->out_stage_2 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_2_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_2_5 = outlet_new(&x->x_obj, &s_float);

	x->out_stage_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_3_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_3_5 = outlet_new(&x->x_obj, &s_float);

	x->out_stage_4 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_4_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_4_5 = outlet_new(&x->x_obj, &s_float);

	x->out_stage_5 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_5_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_5_5 = outlet_new(&x->x_obj, &s_float);

	x->out_stage_6 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_6_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_6_5 = outlet_new(&x->x_obj, &s_float);

	x->out_stage_7 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_7_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_7_5 = outlet_new(&x->x_obj, &s_float);

	x->out_stage_8 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_8_3 = outlet_new(&x->x_obj, &s_float);
	x->out_stage_8_5 = outlet_new(&x->x_obj, &s_float);


  return (void *)x;
}

/**
 * Calculates the intervals in perfect temperament, depending on the Keynote and assigns them to the outlets
 */

void ph_pitchperfect_calculate(ph_pitchperfect *x, float keynote)
{
								 //Reference
	float grSek = keynote *9/8;  // D
	float grTerz = keynote *5/4; // E
	float quarte = keynote* 4/3; // F
	float quinte = keynote* 3/2; // G
	float grSext = keynote* 5/3; // A
	float grSept = keynote *15/8; //H
	float oktave = keynote *2;    //C
	//verhältnisse nach der reinen stimmung

	outlet_float(x->out_stage_1, keynote);
	outlet_float(x->out_stage_1_3, grTerz);
	outlet_float(x->out_stage_1_5, quinte);

	outlet_float(x->out_stage_2, grSek);
	outlet_float(x->out_stage_2_3, quarte);
	outlet_float(x->out_stage_2_5, grSext);

	outlet_float(x->out_stage_3, grTerz);
	outlet_float(x->out_stage_3_3, quinte);
	outlet_float(x->out_stage_3_5, grSept);

	outlet_float(x->out_stage_4, quarte);
	outlet_float(x->out_stage_4_3, grSext);
	outlet_float(x->out_stage_4_5, oktave);

	//Multiply 2 to get the Triad without inversion
	outlet_float(x->out_stage_5, quinte);
	outlet_float(x->out_stage_5_3, grSept);
	outlet_float(x->out_stage_5_5, grSek*2);

	outlet_float(x->out_stage_6, grSext);
	outlet_float(x->out_stage_6_3, oktave);
	outlet_float(x->out_stage_6_5, grTerz*2);

	outlet_float(x->out_stage_7, grSept);
	outlet_float(x->out_stage_7_3, grSek*2);
	outlet_float(x->out_stage_7_5, quarte*2);

	outlet_float(x->out_stage_8, oktave);
	outlet_float(x->out_stage_8_3, grTerz*2);
	outlet_float(x->out_stage_8_5, quinte*2);

}

/**Creates a new Class and assigns Methods of the PD-Object
 */

void ph_pitchperfect_setup(void) {
  /* create a new class */
	ph_pitchperfect_class = class_new(gensym("ph_pitchperfect"),        /* the object's name is "helloworld" */
			       (t_newmethod)ph_pitchperfect_new, /* the object's constructor is "helloworld_new()" */
			       0,                           /* no special destructor */
			       sizeof(ph_pitchperfect),        /* the size of the data-space */
			       CLASS_DEFAULT,               /* a normal pd object */
			       0);                          /* no creation arguments */


  class_addmethod(ph_pitchperfect_class, (t_method)ph_pitchperfect_calculate, gensym("keynote"), A_DEFFLOAT, 0);

}
