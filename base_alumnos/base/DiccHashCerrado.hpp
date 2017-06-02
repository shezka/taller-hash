#ifndef DICCHASHCERRADO_H_
#define DICCHASHCERRADO_H_

#include "Lista.h"
#include <string>

#ifndef TAM_TABLA_INI
	#define TAM_TABLA_INI 100
#endif
#ifndef UMBRAL_FC
	#define UMBRAL_FC	  0.75
#endif

typedef std::string String;

namespace aed2 {

	template<class S>
	class DiccHashCerrado {
	public:

		typedef std::string K;

		DiccHashCerrado();
		~DiccHashCerrado();

		bool 	 Definido(const K& clave) const;
		void 	 Definir(const K& clave, const S& significado);
		S& 		 Significado(const K& clave);
		void 	 Borrar(const K& clave);
		Nat 	 CantClaves() const;

		// solo para test!!
		Lista<K> Claves() const;
		float    factorCarga() const;
		Nat      colisiones() const;

	private:

		struct TElem{
				K 	 clave;
				S 	 signif;
				
				TElem(const K& c, const S& v) : clave(c), signif(v) {}
			};

		Lista<TElem>*   _tabla;
		
		// IMPORTANTE: No olvidarse de mantener actualizadas las siguientes variables:
		Nat             _cant_elems;
		Nat             _tam;

		Nat fn_hash (const String& str) const {
// POST: the index of entry is returned
//                  int sum = 0;
//                for (int k = 0; k < str.length(); k++)
//                    sum = sum + int(str[k]);
//                return  sum % _tam;
            int seed = 131;
            unsigned long hash = 0;
            for(int i = 0; i < str.length(); i++)
            {
                hash = (hash * seed) + str[i];
            }
            return hash % _tam;

		}

		// Aux (por si la necesitan)
		Nat charToNat(char c) const {
			return (Nat)(c);
		}

		void redimensionarTabla(){
			//assert(false);
			Lista<TElem>* tablaAux = _tabla;
            _tabla = new Lista<TElem>();
            _tam = 2 * _tam;
            int i = 0;
            while (i < tablaAux->Longitud())
            {

                auto it = tablaAux[i].CrearIt();
                while (it.HaySiguiente())
                {
                    TElem siguiente = it.Siguiente();
                    it.Avanzar();
				//	if (it.HaySiguiente())
				//	{
						this->Definir(siguiente.clave, siguiente.signif);
						//_tabla[fn_hash(siguiente.clave)].(siguiente);
				//	}
                }
                i++;
            }
           // delete tablaAux;
		}
	};

	/********************************************************************************
	 * Implementacion
	 ********************************************************************************/

	template<class S>
	DiccHashCerrado<S>::DiccHashCerrado() : _cant_elems(0), _tam(TAM_TABLA_INI) {
		_tabla = new Lista<TElem>[TAM_TABLA_INI];
	}

	template<class S>
	DiccHashCerrado<S>::~DiccHashCerrado() {
		delete [] _tabla;
	}

	template<class S>
	bool DiccHashCerrado<S>::Definido(const K& clave) const {
		//assert(false);
        auto it = _tabla[fn_hash(clave)].CrearIt();
        while (it.HaySiguiente())
        {
            if (it.Siguiente().clave == clave)
            {
                return true;
            }
            it.Avanzar();
        }
        return false;
		// TODO: Buscar la clave en el vector y ver si está ocupada. 
		// Utilizar la función de hash para obtener la posición inicial del vector
	}


	template<class S>
	void DiccHashCerrado<S>::Definir(const K& clave, const S& significado) {
		if(factorCarga() > UMBRAL_FC)
			redimensionarTabla();
        auto tablita = _tabla[fn_hash(clave)];
            if (Definido(clave))
            {

                auto it = tablita.CrearIt();
                while (it.HaySiguiente())
                {
                    if (it.Siguiente().clave == clave)
                    {
                        it.Siguiente().signif = significado;
                        break;
                    }
                    it.Avanzar();
                }
            }
        else {
                TElem telem(clave, significado);
                tablita.AgregarAdelante(telem);
                this->_cant_elems++;
            }
        _tabla[fn_hash(clave)] = tablita;

		// Si el elemento ya estaba en el Diccionario, entonces redefinir su significado
		// TODO: Crear el objeto TElem y ubicarlo en la posición del vector correspondiente
	}


	template<class S>
	S& DiccHashCerrado<S>::Significado(const K& clave) {
		assert(Definido(clave));
		auto it = _tabla[fn_hash(clave)].CrearIt();
        while (it.HaySiguiente())
        {
            if (it.Siguiente().clave == clave)
            {
                return it.Siguiente().signif;;
            }
            it.Avanzar();
        }
		// TODO: Igual a definido, devolviendo el significado del objeto obtenido
	}


	template<class S>
	void DiccHashCerrado<S>::Borrar(const K& clave) {
		assert(Definido(clave));
        auto it = _tabla[fn_hash(clave)].CrearIt();
        while (it.HaySiguiente())
        {
            if (it.Siguiente().clave == clave)
            {
                it.EliminarSiguiente();
                _cant_elems--;
                break;
            }
            it.Avanzar();
        }
		// TODO
	}

	template<class S>
	Nat DiccHashCerrado<S>::CantClaves() const {
		return _cant_elems;
	}

	// SOLO PARA TEST
	template<class S>
	Lista<typename DiccHashCerrado<S>::K> DiccHashCerrado<S>::Claves() const {
		Lista<K> ret;
		typename Lista<TElem>::const_Iterador it;

		for(Nat i=0; i < _tam; i++){
			for(it = _tabla[i].CrearIt(); it.HaySiguiente(); it.Avanzar())
				ret.AgregarAtras(it.Siguiente().clave);
		}

		return ret;
	}

	// SOLO PARA TEST
	template<class S>
	float DiccHashCerrado<S>::factorCarga() const {

		return float(_cant_elems)/_tam;
	}

	// SOLO PARA TEST
	template<class S>
	Nat DiccHashCerrado<S>::colisiones() const {

		Nat ret = 0;
		for(Nat i=0; i < _tam; i++){
			if (_tabla[i].Longitud() > 1)
				ret = ret + _tabla[i].Longitud() -1;
		}

		return ret;
	}
} /* namespace aed2 */

#endif /* DICCHASHCERRADO_H_ */
