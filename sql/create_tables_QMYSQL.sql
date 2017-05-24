-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Creato il: Mag 13, 2017 alle 19:30
-- Versione del server: 10.0.29-MariaDB
-- Versione PHP: 7.0.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
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

CREATE TABLE IF NOT EXISTS `listino_prezzi` (
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
  `pz_pubblico` float NOT NULL,
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

CREATE TABLE IF NOT EXISTS `testata_listino` (
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

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `listino_prezzi`
--
ALTER TABLE `listino_prezzi`
  ADD UNIQUE KEY `sigla_marchio` (`sigla_marchio`,`codice_prodotto`);

--
-- Indici per le tabelle `testata_listino`
--
ALTER TABLE `testata_listino`
  ADD UNIQUE KEY `sigla_azienda` (`sigla_azienda`,`numero`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
