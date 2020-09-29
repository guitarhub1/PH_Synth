/**
 * @file ph_formant_osc.c
 * An Pure Data Object to generate sinus and any other waveforms made by array
 *
 * @author Hannes Hügel and Michael Pohn<br>
 * Audiocommunication Group, Technical University Berlin
 *
 */

#include "m_pd.h"
#include "vas_osc.h"

static t_class *ph_formant_osc_tilde_class;

/**
 * struct to define Inlets and Outlets of PD-Object
 *
 */

typedef struct ph_formant_osc_tilde
{
    t_object  x_obj;        /**< necessary for every signal object in Pure Data */
    
    t_sample f;             /**< necessary for signal objects, float dummy dataspace for converting a float to signal */
    vas_osc *osc;           /**< necessary object for customize signal processing */
    t_word *table;          /**< necessary for array objects */
    
    t_outlet *out;          /**< signal outlet for the generated signal level of the incoming signal with all adaptable parameters */
} ph_formant_osc_tilde;

/**
 * calculates the volume adjusted output vector
 * w = A pointer to the object, input and output vectors.
 */

t_int *ph_formant_osc_perform(t_int *w)
{
	ph_formant_osc_tilde *x = (ph_formant_osc_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);
    
    vas_osc_process(x->osc, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);       /**< a pointer to the signal chain right behind the formant_osc_tilde object.*/
}

/**
 * adds formant_osc_tilde_perform to the signal chain
 * x = a pointer the formant_osc_tilde object <br>
 * sp = a pointer the input and output vectors <br>
 */

void ph_formant_osc_tilde_dsp(ph_formant_osc_tilde *x, t_signal **sp)
{
    dsp_add(ph_formant_osc_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * frees our object. <br>
 * x = a pointer the formant_osc_tilde object <br>
 */

void ph_formant_osc_tilde_free(ph_formant_osc_tilde *x)
{
    outlet_free(x->out);
    vas_osc_free(x->osc);
}

/**
 * creates a new formant_osc_tilde object.<br>
 */

void *ph_formant_osc_tilde_new()
{
	ph_formant_osc_tilde *x = (ph_formant_osc_tilde *)pd_new(ph_formant_osc_tilde_class);
    
    //The main inlet is created automatically
    x->out = outlet_new(&x->x_obj, &s_signal);
    x->osc = vas_osc_new(44100);

    return (void *)x;
}

/**
 * checks structs of arrays and reads the IRs from them
 */

void ph_getArray(ph_formant_osc_tilde *x, t_symbol *arrayname, t_word **array, int *length)
{
    t_garray *a;

    if (!(a = (t_garray *)pd_findbyclass(arrayname, garray_class)))
    {
        if (*arrayname->s_name) pd_error(x, "vas_binaural~: %s: no such array",
            arrayname->s_name);
        *array = 0;
    }
    else if (!garray_getfloatwords(a, length, array))
    {
        pd_error(x, "%s: bad template for formant_osc~", arrayname->s_name);
        *array = 0;
    }
    else
    {
        post("Reading IRs from array %s", arrayname->s_name);
    }
}

/**
 * writes an array for free adjustable waveforms to the waveform generating class vas_osc
 */

void ph_write2FloatArrayWavetable(ph_formant_osc_tilde *x)
{
    for (int i=0;i<44100; i++)
        x->osc->lookupWaveTable[i] = x->table[i].w_float;
}

/**
 * reads an array from the input for free adjustable fundamental waveforms
 */

void ph_formant_osc_tilde_setWaveTabel(ph_formant_osc_tilde *x, t_symbol *name)
{
    int length = 0;
    ph_getArray(x, name, &x->table, &length);
    ph_write2FloatArrayWavetable(x);

    post("Waveform in %s is set for the fundamental !", name->s_name);
}

/**
 * writes an array for the first formant envelope to the formant controlling class vas_osc
 */

void ph_write2FloatArrayFormantTabel1(ph_formant_osc_tilde *x)
{
    for (int i=0;i<44100; i++)
        x->osc->lookupFormantTable1[i] = x->table[i].w_float;
}

/**
 * reads an array from the input for the first formant envelope
 */

void ph_formant_osc_tilde_setFormantTabel1(ph_formant_osc_tilde *x, t_symbol *name)
{
    int length = 0;
    ph_getArray(x, name, &x->table, &length);
    ph_write2FloatArrayFormantTabel1(x);
    
    post("Waveform in %s is set for the envelope in the first formant !", name->s_name);
}

/**
 * writes an array for the second formant envelope to the formant controlling class vas_osc
 */

void ph_write2FloatArrayFormantTabel2(ph_formant_osc_tilde *x)
{
    for (int i=0;i<44100; i++)
        x->osc->lookupFormantTable2[i] = x->table[i].w_float;
}

/**
 * reads an array from the input for the second formant envelope
 */

void ph_formant_osc_tilde_setFormantTabel2(ph_formant_osc_tilde *x, t_symbol *name)
{
    int length = 0;
    ph_getArray(x, name, &x->table, &length);
    ph_write2FloatArrayFormantTabel2(x);
    
    post("Waveform in %s is set for the envelope in the second formant !", name->s_name);

}

/**
 * writes an array for the third formant envelope to the formant controlling class vas_osc
 */

void ph_write2FloatArrayFormantTabel3(ph_formant_osc_tilde *x)
{
    for (int i=0;i<44100; i++)
        x->osc->lookupFormantTable3[i] = x->table[i].w_float;
}

/**
 * reads an array from the input for the third formant envelope
 */

void ph_formant_osc_tilde_setFormantTabel3(ph_formant_osc_tilde *x, t_symbol *name)
{
    int length = 0;
    ph_getArray(x, name, &x->table, &length);
    ph_write2FloatArrayFormantTabel3(x);

    post("Waveform in %s is set for the envelope in the third formant !", name->s_name);

}

/**
 * writes an array for the fourth formant envelope to the formant controlling class vas_osc
 */

void ph_write2FloatArrayFormantTabel4(ph_formant_osc_tilde *x)
{
    for (int i=0;i<44100; i++)
        x->osc->lookupFormantTable4[i] = x->table[i].w_float;
}

/**
 * reads an array from the input for the fourth formant envelope
 */

void ph_formant_osc_tilde_setFormantTabel4(ph_formant_osc_tilde *x, t_symbol *name)
{
    int length = 0;
    ph_getArray(x, name, &x->table, &length);
    ph_write2FloatArrayFormantTabel4(x);
    
    post("Waveform in %s is set for the envelope in the fourth formant !", name->s_name);

}

/**
 * load the frequency as float from the input to pitch the oscillator
 */

void ph_formant_osc_tilde_setFrequency(ph_formant_osc_tilde *x, float frequency)
{
    vas_osc_setFrequency(x->osc, frequency);
}

/**
 * load a number as float from the input to set the number of harmonics
 */

void ph_formant_osc_tilde_setHarmonics(ph_formant_osc_tilde *x, float harmonics)
{
    vas_osc_setHarmonics(x->osc, harmonics);
}

/**
 * load a float value from the input to shift the time of the formants envelope duration
 */

void ph_formant_osc_tilde_setFrequencyFormants(ph_formant_osc_tilde *x, float frequency)
{
    vas_osc_setFormantFrequency(x->osc, frequency);
}

/**
 * load more float values from the input to set the range of formants between
 */

void ph_formant_osc_tilde_setFormantrange(ph_formant_osc_tilde *x, float formant0, float formant1, float formant2, float formant3, float formant4)
{
    vas_osc_setFormantrange(x->osc, formant0, formant1, formant2, formant3, formant4);
}

/**
 * reset the oscillator frequency to the default sinus
 */

void ph_formant_osc_tilde_setResetWaveform(ph_formant_osc_tilde *x)
{
    vas_osc_setWavetable(x->osc);
    post("Frequency is a ordinary sinus again !");
}

/**
 * reset all arrays of the formant envelopes to continous
 */

void ph_formant_osc_tilde_setResetFormants(ph_formant_osc_tilde *x)
{
    vas_osc_setFormants(x->osc);
    post("All formants are set continously !");
}

/**Creates a new Class and assigns Methods of the PD-Object
 */

void ph_formant_osc_tilde_setup(void)
{
	  ph_formant_osc_tilde_class = class_new(gensym("ph_formant_osc~"),
                                      (t_newmethod)ph_formant_osc_tilde_new,
                                      (t_method)ph_formant_osc_tilde_free,
                            sizeof(ph_formant_osc_tilde),
                                      CLASS_DEFAULT, A_DEFFLOAT, 0);
        
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_dsp, gensym("dsp"), 0);
    
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setFrequency, gensym("frequency"), A_DEFFLOAT, 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setHarmonics, gensym("numberofharmonics"), A_DEFFLOAT, 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setFrequencyFormants, gensym("formantfrequency"), A_DEFFLOAT, 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setWaveTabel, gensym("loadwaveform"),
                    A_SYMBOL, 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setFormantrange, gensym("formantrange"), A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, 0);

      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setFormantTabel1, gensym("loadformant1"),
                    A_SYMBOL, 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setFormantTabel2, gensym("loadformant2"),
                    A_SYMBOL, 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setFormantTabel3, gensym("loadformant3"),
                    A_SYMBOL, 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setFormantTabel4, gensym("loadformant4"),
                  A_SYMBOL, 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setResetWaveform, gensym("resetwaveform"), 0);
      class_addmethod(ph_formant_osc_tilde_class, (t_method)ph_formant_osc_tilde_setResetFormants, gensym("resetformant"), 0);
    
    
    
      CLASS_MAINSIGNALIN(ph_formant_osc_tilde_class, ph_formant_osc_tilde, f);
}
