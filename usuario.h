#ifndef USUARIO_H
#define USUARIO_H

#include <QString>



class Usuario
{
public:
    QString usuario;
    QString contraseña;
    QString nombre;
    QString curp;
    int idEstado;
    QString estado;
    int idVotante;
    int idCandidato;
    QString propuesta;
    int idPartido;
    QString partido;
    int idEleccion;
    QString eleccion;
    QString fase;

    friend class votanteWin;
    friend class candidatoWin;
    friend class MainWindow;
    friend class perfilWin;
    friend class resultadosWin;
    friend class votacionWin;


    Usuario();
};

#endif // USUARIO_H
