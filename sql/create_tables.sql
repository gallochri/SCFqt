-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Creato il: Mag 06, 2017 alle 13:50
-- Versione del server: 5.7.18-log
-- Versione PHP: 5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `testdb`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `listino_prezzi`
--

CREATE TABLE `listino_prezzi` (
  `sigla_marchio` varchar(3) NOT NULL,
  `codice_prodotto` varchar(16) NOT NULL,
  `codice_EAN` varchar(13) NOT NULL,
  `descrizione_prodotto` varchar(43) NOT NULL,
  `qta_cartone` int(5) NOT NULL,
  `qta_multipla_ordinazione` int(5) NOT NULL,
  `qta_minima_ordinazione` int(5) NOT NULL,
  `qta_massima_ordinazione` int(6) NOT NULL,
  `lead_time` varchar(1) NOT NULL,
  `pz_rivenditore` float NOT NULL,
  `pz_pubblice` float NOT NULL,
  `moltiplicatore` int(6) NOT NULL,
  `codice_valuta` varchar(3) NOT NULL,
  `unita_misura` varchar(3) NOT NULL,
  `prodotto_composto` varchar(1) NOT NULL,
  `stato_del_prodotto` varchar(1) NOT NULL,
  `data_variazione` date NOT NULL,
  `famiglia_sconto` varchar(18) NOT NULL,
  `famiglia_statistica` varchar(18) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Struttura della tabella `testata_listino`
--

CREATE TABLE `testata_listino` (
  `id_tracciato` char(20) NOT NULL,
  `sigla_azienda` char(3) NOT NULL,
  `partita_iva` char(11) NOT NULL,
  `numero` char(6) NOT NULL,
  `decorrenza` date NOT NULL,
  `data_variazione` date NOT NULL,
  `descrizione` char(30) NOT NULL,
  `filler` char(39) NOT NULL,
  `versione_tracciato` char(3) NOT NULL,
  `data_decorrenza_gr` char(8) NOT NULL,
  `isopartita` char(16) NOT NULL,
  `filler2` char(81) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
