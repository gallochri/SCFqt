create table listino_prezzi
(
	sigla_marchio varchar(3) not null,
	codice_prodotto varchar(16) not null,
	codice_EAN varchar(13) not null,
	descrizione_prodotto varchar(43) not null,
	qta_cartone int(5) not null,
	qta_multipla_ordinazione int(5) not null,
	qta_minima_ordinazione int(5) not null,
	qta_massima_ordinazione int(6) not null,
	lead_time varchar(1) not null,
	pz_rivenditore float not null,
	pz_pubblico float not null,
	moltiplicatore int(6) not null,
	codice_valuta varchar(3) not null,
	unita_misura varchar(3) not null,
	prodotto_composto varchar(1) not null,
	stato_del_prodotto varchar(1) not null,
	data_variazione date not null,
	famiglia_sconto varchar(18) not null,
	famiglia_statistica varchar(18) not null,
	constraint sigla_marchio
		unique (sigla_marchio, codice_prodotto)
)
;

create table testata_listino
(
	id_tracciato char(20) not null,
	sigla_azienda char(3) not null,
	partita_iva char(11) not null,
	numero char(6) not null,
	decorrenza date not null,
	data_variazione date not null,
	descrizione char(30) not null,
	filler char(39) not null,
	versione_tracciato char(3) not null,
	data_decorrenza_gr char(8) not null,
	isopartita char(16) not null,
	filler2 char(81) not null,
	constraint sigla_azienda
		unique (sigla_azienda, numero)
)
;

