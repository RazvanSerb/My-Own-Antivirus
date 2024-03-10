#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int putere(int a, int b)
{
	int rez = 1;
	for (int i = 1; i <= b; i++)
		rez = rez * a;
	return rez;
}

double numar_char_to_double(char *sir)
{
	double numar = 0;
	char csir[1000];
	snprintf(csir, sizeof(csir), "%s", sir);
	int numar1 = 0, numar2 = 0;
	char *punct = strchr(csir, '.');
	*punct = '\0';
	numar1 = atoi(csir);
	snprintf(csir, sizeof(csir), "%s", punct + 1);
	numar2 = atoi(csir);
	numar = (double)(numar1) + (double)(numar2) / (putere(10, strlen(csir)));
}

void TASK1(void)
{
	FILE *fisierin = fopen("data/urls/urls.in", "rt");
	FILE *fisierout = fopen("urls-predictions.out", "wt");
	char url[1000], url_domain[1000], sir[1000];
	while (1) {
		fgets(url, 1000, fisierin);
		url[strlen(url) - 1] = '\0';
		if (feof(fisierin))
			break;
		char *delimitator = strchr(strchr(url, '.') + 1, '/');
		if (delimitator) {
			*delimitator = '\0';
			snprintf(url_domain, sizeof(url_domain), "%s", url);
			*delimitator = '/';
		} else {
			snprintf(url_domain, sizeof(url_domain), "%s", url);
		}
		int BEC = 0;
		FILE *bazadateurl = fopen("data/urls/domains_database", "rt");
		while (1) {
			fgets(sir, 1000, bazadateurl);
			sir[strlen(sir) - 1] = '\0';
			if (feof(bazadateurl))
				break;
			if (strstr(url_domain, sir)) {
				BEC = 1;
				break;
			}
		}
		fclose(bazadateurl);
		if (strstr(url, ".exe") || strstr(url, ".bin"))
			BEC = 1;
		for (int i = 0; i < strlen(url_domain); i++)
			if (url_domain[i] >= '0' && url_domain[i] <= '9') {
				BEC = 1;
				break;
			}
		fprintf(fisierout, "%d\n", BEC);
	}
	fclose(fisierin);
	fclose(fisierout);
}

void TASK2(void)
{
	FILE *fisierin = fopen("data/traffic/traffic.in", "rt");
	FILE *fisierout = fopen("traffic-predictions.out", "wt");
	char sir[1000]; char flow_duration[1000]; double flow_pkts_payload_avg = 0;
	fgets(sir, 1000, fisierin);
	sir[strlen(sir) - 1] = '\0';
	int poz = 0, poz_fd = 0, poz_fppa = 0;
	char *virgula = strchr(sir, ',');
	while (virgula) {
		poz++;
		*virgula = '\0';
		if (strcmp(sir, "flow_duration") == 0)
			poz_fd = poz;
		if (strcmp(sir, "flow_pkts_payload.avg") == 0)
			poz_fppa = poz;
		char csir[1000];
		snprintf(csir, sizeof(sir), "%s", virgula + 1);
		snprintf(sir, sizeof(sir), "%s", csir);
		virgula = strchr(sir, ',');
	}
	if (!virgula) {
		poz++;
		if (strcmp(sir, "flow_duration") == 0)
			poz_fd = poz;
		if (strcmp(sir, "flow_pkts_payload.avg") == 0)
			poz_fppa = poz;
	}
	while (1) {
		fgets(sir, 1000, fisierin);
		sir[strlen(sir) - 1] = '\0';
		if (feof(fisierin))
			break;
		poz = 0;
		virgula = strchr(sir, ',');
		while (virgula) {
			poz++;
			*virgula = '\0';
			if (poz == poz_fd)
				snprintf(flow_duration, sizeof(flow_duration), "%s", sir);
			if (poz == poz_fppa)
				flow_pkts_payload_avg = numar_char_to_double(sir);
			char csir[1000];
			snprintf(csir, sizeof(sir), "%s", virgula + 1);
			snprintf(sir, sizeof(sir), "%s", csir);
			virgula = strchr(sir, ',');
		}
		if (!virgula) {
			poz++;
			if (poz == poz_fd)
				snprintf(flow_duration, sizeof(flow_duration), "%s", sir);
			if (poz == poz_fppa)
				flow_pkts_payload_avg = numar_char_to_double(sir);
		}
		int BEC = 0;
		if (flow_pkts_payload_avg != (float)(0)) {
			if (flow_duration[0] != '0') {
				BEC = 1;
				goto afisare;
			}
			if (flow_duration[7] != '0' || flow_duration[8] != '0') {
				BEC = 1;
				goto afisare;
			}
		    if (flow_duration[10] != '0' || flow_duration[11] != '0') {
				BEC = 1;
				goto afisare;
			}
			if (flow_duration[13] != '0' || flow_duration[14] != '0') {
				BEC = 1;
				if (flow_duration[13] == '0' && flow_duration[14] == '1')
					if (flow_duration[15] == '\0')
						BEC = 0;
				goto afisare;
			}
		}
afisare:
		fprintf(fisierout, "%d\n", BEC);
	}
	fclose(fisierin);
	fclose(fisierout);
}

int main(void)
{
	TASK1();
	TASK2();
	return 0;
}
