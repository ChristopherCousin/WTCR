--
-- PostgreSQL database dump
--

-- Dumped from database version 10.6
-- Dumped by pg_dump version 10.6

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: actions; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.actions (
    id integer NOT NULL,
    name character varying(255)
);


ALTER TABLE public.actions OWNER TO usuario;

--
-- Name: actions_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.actions_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.actions_id_seq OWNER TO usuario;

--
-- Name: actions_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.actions_id_seq OWNED BY public.actions.id;


--
-- Name: employee; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.employee (
    id integer NOT NULL,
    name character varying(15) NOT NULL,
    surname1 character varying(15),
    surname2 character varying(15),
    birthdate date,
    identitytype integer,
    identitynum character varying(255),
    serialtypeid integer,
    serialid integer
);


ALTER TABLE public.employee OWNER TO usuario;

--
-- Name: employee_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.employee_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.employee_id_seq OWNER TO usuario;

--
-- Name: employee_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.employee_id_seq OWNED BY public.employee.id;


--
-- Name: history; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.history (
    id integer NOT NULL,
    serialid integer,
    date date,
    hour time without time zone,
    actionid integer
);


ALTER TABLE public.history OWNER TO usuario;

--
-- Name: history_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.history_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.history_id_seq OWNER TO usuario;

--
-- Name: history_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.history_id_seq OWNED BY public.history.id;


--
-- Name: identitytype; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.identitytype (
    id integer NOT NULL,
    name character varying(255)
);


ALTER TABLE public.identitytype OWNER TO usuario;

--
-- Name: identitytype_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.identitytype_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.identitytype_id_seq OWNER TO usuario;

--
-- Name: identitytype_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.identitytype_id_seq OWNED BY public.identitytype.id;


--
-- Name: serialstorage; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.serialstorage (
    id integer NOT NULL,
    typeid integer NOT NULL,
    "serialID" integer NOT NULL,
    active boolean DEFAULT false,
    expired boolean DEFAULT true
);


ALTER TABLE public.serialstorage OWNER TO usuario;

--
-- Name: serialstorage_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.serialstorage_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.serialstorage_id_seq OWNER TO usuario;

--
-- Name: serialstorage_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.serialstorage_id_seq OWNED BY public.serialstorage.id;


--
-- Name: serialtype; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.serialtype (
    id integer NOT NULL,
    name character varying(50)
);


ALTER TABLE public.serialtype OWNER TO usuario;

--
-- Name: serialtype_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.serialtype_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.serialtype_id_seq OWNER TO usuario;

--
-- Name: serialtype_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.serialtype_id_seq OWNED BY public.serialtype.id;


--
-- Name: actions id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.actions ALTER COLUMN id SET DEFAULT nextval('public.actions_id_seq'::regclass);


--
-- Name: employee id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee ALTER COLUMN id SET DEFAULT nextval('public.employee_id_seq'::regclass);


--
-- Name: history id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.history ALTER COLUMN id SET DEFAULT nextval('public.history_id_seq'::regclass);


--
-- Name: identitytype id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.identitytype ALTER COLUMN id SET DEFAULT nextval('public.identitytype_id_seq'::regclass);


--
-- Name: serialstorage id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.serialstorage ALTER COLUMN id SET DEFAULT nextval('public.serialstorage_id_seq'::regclass);


--
-- Name: serialtype id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.serialtype ALTER COLUMN id SET DEFAULT nextval('public.serialtype_id_seq'::regclass);


--
-- Data for Name: actions; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.actions (id, name) FROM stdin;
1	Start Working
\.


--
-- Data for Name: employee; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.employee (id, name, surname1, surname2, birthdate, identitytype, identitynum, serialtypeid, serialid) FROM stdin;
1	Pepito	Perez	Mola	2000-01-01	1	12312231P	1	1
\.


--
-- Data for Name: history; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.history (id, serialid, date, hour, actionid) FROM stdin;
\.


--
-- Data for Name: identitytype; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.identitytype (id, name) FROM stdin;
1	DNI
\.


--
-- Data for Name: serialstorage; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.serialstorage (id, typeid, "serialID", active, expired) FROM stdin;
1	1	1	f	t
\.


--
-- Data for Name: serialtype; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.serialtype (id, name) FROM stdin;
1	ean13
\.


--
-- Name: actions_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.actions_id_seq', 1, true);


--
-- Name: employee_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.employee_id_seq', 2, true);


--
-- Name: history_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.history_id_seq', 1, false);


--
-- Name: identitytype_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.identitytype_id_seq', 1, true);


--
-- Name: serialstorage_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.serialstorage_id_seq', 1, true);


--
-- Name: serialtype_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.serialtype_id_seq', 1, true);


--
-- Name: actions PKaction; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.actions
    ADD CONSTRAINT "PKaction" PRIMARY KEY (id);


--
-- Name: employee PKemployee; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "PKemployee" PRIMARY KEY (id);


--
-- Name: history PKhistory; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.history
    ADD CONSTRAINT "PKhistory" PRIMARY KEY (id);


--
-- Name: identitytype PKidentityType; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.identitytype
    ADD CONSTRAINT "PKidentityType" PRIMARY KEY (id);


--
-- Name: serialstorage PKserialStorage; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.serialstorage
    ADD CONSTRAINT "PKserialStorage" PRIMARY KEY (id);


--
-- Name: serialtype PKserialType; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.serialtype
    ADD CONSTRAINT "PKserialType" PRIMARY KEY (id);


--
-- Name: employee FKIdentityType; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "FKIdentityType" FOREIGN KEY (identitytype) REFERENCES public.identitytype(id);


--
-- Name: employee FKSerial; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "FKSerial" FOREIGN KEY (serialid) REFERENCES public.serialstorage(id);


--
-- Name: employee FKSerialType; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.employee
    ADD CONSTRAINT "FKSerialType" FOREIGN KEY (serialtypeid) REFERENCES public.serialtype(id);


--
-- PostgreSQL database dump complete
--

